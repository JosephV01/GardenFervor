// Copyright Epic Games, Inc. All Rights Reserved.

#include "GardenFervorInvestorDemoS3Director.h"

#include "GardenFervorCohortObservabilityHelpers.h"
#include "GardenFervorCohortStockHelpers.h"
#include "GardenFervorPhysicalEconomySubsystem.h"
#include "GardenFervorPhysicalResourceTypes.h"
#include "GardenFervorProjectSubsystem.h"
#include "GardenFervorSitePrepTypes.h"
#include "GardenFervorTaskSubsystem.h"
#include "GardenFervorTaskTypes.h"
#include "GardenFervorUnitBase.h"
#include "GardenFervorUnitDefinition.h"
#include "GardenFervorUnitTaskAgent.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/TextRenderActor.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"

DEFINE_LOG_CATEGORY_STATIC(LogGardenFervorInvestorDemoS3Dir, Log, All);

namespace InvestorDemoS3DirPrivate
{
	static const FName KeyIntention(TEXT("INTENTION"));
	static const FName KeyProject(TEXT("PROJECT"));
	static const FName KeyWorkSite(TEXT("WORKSITE"));
	static const FName KeyU1(TEXT("U1"));
	static const FName KeyU2(TEXT("U2"));
	static const FName KeyU3(TEXT("U3"));
	static const FName KeyStockA(TEXT("STOCK_A"));
	static const FName KeyStockB(TEXT("STOCK_B"));
	static const FName KeyEnService(TEXT("EN_SERVICE"));
	static const FName KeyHud(TEXT("HUD"));

	static bool NameMatchesKey(const FString& Name, const FName& Key)
	{
		const FString K = Key.ToString();
		if (Name.Contains(K, ESearchCase::IgnoreCase))
		{
			return true;
		}
		// Map STOCK_A ↔ "STOCK A"
		if (Key == KeyStockA && (Name.Contains(TEXT("STOCK_A"), ESearchCase::IgnoreCase)
			|| Name.Contains(TEXT("STOCK A"), ESearchCase::IgnoreCase)))
		{
			return true;
		}
		if (Key == KeyStockB && (Name.Contains(TEXT("STOCK_B"), ESearchCase::IgnoreCase)
			|| Name.Contains(TEXT("STOCK B"), ESearchCase::IgnoreCase)))
		{
			return true;
		}
		if (Key == KeyEnService && Name.Contains(TEXT("EN SERVICE"), ESearchCase::IgnoreCase))
		{
			return true;
		}
		if (Key == KeyHud && Name.Contains(TEXT("HUD"), ESearchCase::IgnoreCase))
		{
			return true;
		}
		return false;
	}
}

AGardenFervorInvestorDemoS3Director::AGardenFervorInvestorDemoS3Director()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	bRunning = false;
}

void AGardenFervorInvestorDemoS3Director::StartPresentation()
{
	if (bRunning)
	{
		UE_LOG(LogGardenFervorInvestorDemoS3Dir, Warning, TEXT("InvestorDemo S3 already running"));
		return;
	}

	bRunning = true;
	bSucceeded = false;
	PeakStockA = 0.f;
	ProjectId = FGardenFervorProjectId{};
	UnitU1 = nullptr;
	UnitU2 = nullptr;
	UnitU3 = nullptr;
	EnterPhase(EPhase::BootLayout);
	UE_LOG(LogGardenFervorInvestorDemoS3Dir, Display, TEXT("InvestorDemo S3 presentation started (async)"));
}

void AGardenFervorInvestorDemoS3Director::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (bRunning)
	{
		Advance(DeltaSeconds);
	}
	FaceLabelsToCamera();
}

void AGardenFervorInvestorDemoS3Director::EnterPhase(EPhase NewPhase)
{
	Phase = NewPhase;
	PhaseTimer = 0.f;
}

bool AGardenFervorInvestorDemoS3Director::SampleLandscape(const FVector& ApproxXY, FVector& OutLocation) const
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return false;
	}
	const FVector Start(ApproxXY.X, ApproxXY.Y, ApproxXY.Z + 100000.f);
	const FVector End(ApproxXY.X, ApproxXY.Y, ApproxXY.Z - 200000.f);
	FHitResult Hit;
	FCollisionQueryParams Params(NAME_None, true);
	if (World->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		OutLocation = Hit.Location;
		return true;
	}
	OutLocation = ApproxXY;
	return false;
}

void AGardenFervorInvestorDemoS3Director::EnsurePresentationMovable(AActor* Actor) const
{
	if (!Actor)
	{
		return;
	}

	// Targeted: only actors the Demo presentation relocates / scales / faces to camera.
	if (USceneComponent* Root = Actor->GetRootComponent())
	{
		if (Root->Mobility != EComponentMobility::Movable)
		{
			Root->SetMobility(EComponentMobility::Movable);
			UE_LOG(LogGardenFervorInvestorDemoS3Dir, Verbose,
				TEXT("InvestorDemo presentation set Movable: %s"), *Actor->GetActorNameOrLabel());
		}
	}

	TArray<USceneComponent*> Components;
	Actor->GetComponents<USceneComponent>(Components);
	for (USceneComponent* Comp : Components)
	{
		if (Comp && Comp->Mobility != EComponentMobility::Movable)
		{
			Comp->SetMobility(EComponentMobility::Movable);
		}
	}
}

void AGardenFervorInvestorDemoS3Director::SnapActorToLandscape(
	AActor* Actor, const FVector& DesiredXY, float HoverZ) const
{
	if (!Actor)
	{
		return;
	}
	EnsurePresentationMovable(Actor);
	FVector Ground = DesiredXY;
	SampleLandscape(DesiredXY, Ground);
	Actor->SetActorLocation(Ground + FVector(0.f, 0.f, HoverZ));
}

AActor* AGardenFervorInvestorDemoS3Director::FindByKey(const TCHAR* Key) const
{
	const FName K(Key);
	if (const TObjectPtr<AActor>* Found = PlaceholderByKey.Find(K))
	{
		return Found->Get();
	}
	return nullptr;
}

ATextRenderActor* AGardenFervorInvestorDemoS3Director::FindLabel(const TCHAR* Key) const
{
	const FName K(Key);
	if (const TObjectPtr<ATextRenderActor>* Found = LabelByKey.Find(K))
	{
		return Found->Get();
	}
	return nullptr;
}

bool AGardenFervorInvestorDemoS3Director::ResolvePresentationActors()
{
	using namespace InvestorDemoS3DirPrivate;
	PlaceholderByKey.Reset();
	LabelByKey.Reset();
	PlaceholderBaseScale.Reset();

	UWorld* World = GetWorld();
	if (!World)
	{
		return false;
	}

	const TArray<FName> Keys = {
		KeyIntention, KeyProject, KeyWorkSite, KeyU1, KeyU2, KeyU3,
		KeyStockA, KeyStockB, KeyEnService, KeyHud
	};

	for (TActorIterator<AActor> It(World); It; ++It)
	{
		AActor* Actor = *It;
		if (!Actor || Actor == this)
		{
			continue;
		}
		const FString Name = Actor->GetActorNameOrLabel();
		for (const FName& Key : Keys)
		{
			if (!NameMatchesKey(Name, Key))
			{
				continue;
			}
			if (ATextRenderActor* TextActor = Cast<ATextRenderActor>(Actor))
			{
				LabelByKey.Add(Key, TextActor);
			}
			else
			{
				PlaceholderByKey.Add(Key, Actor);
				PlaceholderBaseScale.Add(Key, Actor->GetActorScale3D());
			}
		}
	}

	UE_LOG(LogGardenFervorInvestorDemoS3Dir, Log,
		TEXT("InvestorDemo resolve PH=%d LBL=%d"), PlaceholderByKey.Num(), LabelByKey.Num());
	return PlaceholderByKey.Num() >= 5 && LabelByKey.Num() >= 5;
}

void AGardenFervorInvestorDemoS3Director::PlaceChainOnLandscape()
{
	using namespace InvestorDemoS3DirPrivate;

	// Anchor near documented WorkSite XY; snap Z to Landscape.
	FVector Anchor(0.f, -400.f, 0.f);
	SampleLandscape(Anchor, Anchor);
	WorkSiteCenter = Anchor;

	struct FPlace
	{
		FName Key;
		FVector Offset;
		float Hover;
	};
	const FPlace Places[] = {
		{ KeyIntention, FVector(0.f, -2800.f, 0.f), 120.f },
		{ KeyProject, FVector(0.f, -2000.f, 0.f), 120.f },
		{ KeyWorkSite, FVector(0.f, 0.f, 0.f), 40.f },
		{ KeyU1, FVector(-2200.f, 200.f, 0.f), 100.f },
		{ KeyStockA, FVector(-1500.f, 0.f, 0.f), 100.f },
		{ KeyU2, FVector(0.f, 800.f, 0.f), 100.f },
		{ KeyStockB, FVector(1500.f, 0.f, 0.f), 100.f },
		{ KeyU3, FVector(2200.f, 1200.f, 0.f), 100.f },
		{ KeyEnService, FVector(2200.f, 2200.f, 0.f), 120.f },
		{ KeyHud, FVector(-2800.f, -2800.f, 0.f), 80.f },
	};

	for (const FPlace& P : Places)
	{
		if (AActor* PH = FindByKey(*P.Key.ToString()))
		{
			SnapActorToLandscape(PH, WorkSiteCenter + P.Offset, P.Hover);
		}
		if (ATextRenderActor* Lbl = FindLabel(*P.Key.ToString()))
		{
			SnapActorToLandscape(Lbl, WorkSiteCenter + P.Offset + FVector(0.f, 0.f, 0.f), P.Hover + 180.f);
			if (UTextRenderComponent* Text = Lbl->GetTextRender())
			{
				Text->SetWorldSize(120.f);
				Text->SetHorizontalAlignment(EHTA_Center);
				Text->SetVerticalAlignment(EVRTA_TextCenter);
				Text->SetTextRenderColor(FColor::White);
			}
		}
	}
}

void AGardenFervorInvestorDemoS3Director::AlignStocksToPhysicalEconomy()
{
	using namespace InvestorDemoS3DirPrivate;
	UWorld* World = GetWorld();
	UGardenFervorPhysicalEconomySubsystem* Eco = World
		? World->GetSubsystem<UGardenFervorPhysicalEconomySubsystem>()
		: nullptr;
	UGardenFervorProjectSubsystem* Projects = World
		? World->GetSubsystem<UGardenFervorProjectSubsystem>()
		: nullptr;
	if (!Eco || !Projects || !ProjectId.IsValid())
	{
		return;
	}

	FGardenFervorProjectRecord Project;
	if (!Projects->GetProject(ProjectId, Project))
	{
		return;
	}

	FGardenFervorPhysicalStockId IdA;
	IdA.Value = GardenFervorCohortStockAId(Project);
	FGardenFervorPhysicalStockId IdB;
	IdB.Value = GardenFervorCohortStockBId(Project);
	const FVector LocA = Eco->GetStockLocation(IdA);
	const FVector LocB = Eco->GetStockLocation(IdB);

	if (AActor* PHA = FindByKey(TEXT("STOCK_A")))
	{
		SnapActorToLandscape(PHA, LocA, 100.f);
	}
	if (ATextRenderActor* LblA = FindLabel(TEXT("STOCK_A")))
	{
		SnapActorToLandscape(LblA, LocA, 280.f);
	}
	if (AActor* PHB = FindByKey(TEXT("STOCK_B")))
	{
		SnapActorToLandscape(PHB, LocB, 100.f);
	}
	if (ATextRenderActor* LblB = FindLabel(TEXT("STOCK_B")))
	{
		SnapActorToLandscape(LblB, LocB, 280.f);
	}
}

void AGardenFervorInvestorDemoS3Director::SetLabelText(const TCHAR* Key, const FString& Text)
{
	if (ATextRenderActor* Lbl = FindLabel(Key))
	{
		if (UTextRenderComponent* Comp = Lbl->GetTextRender())
		{
			Comp->SetText(FText::FromString(Text));
			Comp->SetWorldSize(120.f);
		}
	}
}

void AGardenFervorInvestorDemoS3Director::FaceLabelsToCamera()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	APlayerController* PC = World->GetFirstPlayerController();
	if (!PC || !PC->PlayerCameraManager)
	{
		return;
	}
	const FVector CamLoc = PC->PlayerCameraManager->GetCameraLocation();
	for (const TPair<FName, TObjectPtr<ATextRenderActor>>& Pair : LabelByKey)
	{
		ATextRenderActor* Lbl = Pair.Value.Get();
		if (!Lbl)
		{
			continue;
		}
		const FVector ToCam = (CamLoc - Lbl->GetActorLocation()).GetSafeNormal2D();
		if (!ToCam.IsNearlyZero())
		{
			EnsurePresentationMovable(Lbl);
			Lbl->SetActorRotation(ToCam.Rotation());
		}
	}
}

void AGardenFervorInvestorDemoS3Director::SetPlaceholderActive(
	const TCHAR* Key, bool bActive, const FLinearColor& Accent)
{
	AActor* Actor = FindByKey(Key);
	if (!Actor)
	{
		return;
	}

	EnsurePresentationMovable(Actor);

	const FName K(Key);
	const FVector Base = PlaceholderBaseScale.Contains(K)
		? PlaceholderBaseScale[K]
		: FVector::OneVector;
	Actor->SetActorScale3D(bActive ? Base * 1.35f : Base);

	TArray<UStaticMeshComponent*> Meshes;
	Actor->GetComponents<UStaticMeshComponent>(Meshes);
	for (UStaticMeshComponent* Mesh : Meshes)
	{
		if (!Mesh)
		{
			continue;
		}
		UMaterialInstanceDynamic* MID = Mesh->CreateDynamicMaterialInstance(0);
		if (MID)
		{
			const FLinearColor Color = bActive ? Accent : (Accent * 0.35f);
			MID->SetVectorParameterValue(TEXT("Color"), Color);
		}
	}
}

void AGardenFervorInvestorDemoS3Director::ApplyUnitDemoColor(
	AGardenFervorUnitBase* Unit, const FLinearColor& Color) const
{
	if (!Unit)
	{
		return;
	}
	if (UStaticMeshComponent* Mesh = Unit->FindComponentByClass<UStaticMeshComponent>())
	{
		UMaterialInstanceDynamic* MID = Mesh->CreateDynamicMaterialInstance(0);
		if (MID)
		{
			MID->SetVectorParameterValue(TEXT("Color"), Color);
		}
		Mesh->SetRelativeScale3D(FVector(2.4f, 2.4f, 3.2f));
	}
}

AGardenFervorUnitBase* AGardenFervorInvestorDemoS3Director::SpawnDemoUnit(
	EGardenFervorCohortUnitRole CohortRole,
	const FVector& Location,
	const FLinearColor& Color)
{
	UWorld* World = GetWorld();
	if (!World || !ProjectId.IsValid())
	{
		return nullptr;
	}

	const FName UnitId = GardenFervorCohortUnitId(CohortRole);
	UGardenFervorUnitDefinition* Def = NewObject<UGardenFervorUnitDefinition>(World);
	Def->UnitId = UnitId;
	Def->DisplayName = FText::FromName(UnitId);
	Def->Capabilities = GardenFervorCohortUnitCapabilities(CohortRole);
	Def->UnitClass = AGardenFervorUnitBase::StaticClass();
	Def->bIsWorker = true;

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AGardenFervorUnitBase* Unit = World->SpawnActor<AGardenFervorUnitBase>(
		AGardenFervorUnitBase::StaticClass(), Location, FRotator::ZeroRotator, Params);
	if (!Unit)
	{
		return nullptr;
	}

	Unit->ApplyDefinition(Def);
	Unit->MoveSpeed = 1400.f;
	Unit->SnapToGroundAt(Location);
	ApplyUnitDemoColor(Unit, Color);
	Unit->PulseSpawnBeacon(4.f);

	if (UFloatingPawnMovement* Move = Unit->FindComponentByClass<UFloatingPawnMovement>())
	{
		Move->MaxSpeed = 1400.f;
		Move->Acceleration = 9000.f;
	}
	if (UGardenFervorUnitTaskAgent* Agent = Unit->GetTaskAgent())
	{
		Agent->MaterialBatchAmount = 1.f;
		Agent->ExecuteDurationSeconds = 0.55f;
		Agent->PrepareDurationSeconds = 0.1f;
		Agent->SetInstantMode(false); // real travel via UnitTaskAgent / MoveToLocation
		Agent->SetProjectFilter(ProjectId);
		Agent->SetAutonomyEnabled(true);
	}
	return Unit;
}

void AGardenFervorInvestorDemoS3Director::Advance(float DeltaSeconds)
{
	using namespace InvestorDemoS3DirPrivate;
	PhaseTimer += DeltaSeconds;
	UWorld* World = GetWorld();
	if (!World)
	{
		bRunning = false;
		return;
	}

	UGardenFervorProjectSubsystem* Projects = World->GetSubsystem<UGardenFervorProjectSubsystem>();
	UGardenFervorTaskSubsystem* Tasks = World->GetSubsystem<UGardenFervorTaskSubsystem>();
	UGardenFervorPhysicalEconomySubsystem* Eco = World->GetSubsystem<UGardenFervorPhysicalEconomySubsystem>();

	switch (Phase)
	{
	case EPhase::BootLayout:
	{
		if (!ResolvePresentationActors())
		{
			UE_LOG(LogGardenFervorInvestorDemoS3Dir, Warning,
				TEXT("InvestorDemo S3: placeholders/labels incomplete — continuing with what exists"));
		}
		PlaceChainOnLandscape();
		SetLabelText(TEXT("INTENTION"), TEXT("INTENTION\nready"));
		SetLabelText(TEXT("PROJECT"), TEXT("PROJECT\n…"));
		SetLabelText(TEXT("WORKSITE"), TEXT("WORKSITE\n…"));
		SetPlaceholderActive(TEXT("INTENTION"), true, FLinearColor(0.2f, 0.85f, 1.f));
		EnterPhase(EPhase::CreateProject);
		break;
	}
	case EPhase::CreateProject:
	{
		if (!Projects || !Tasks || !Eco)
		{
			UE_LOG(LogGardenFervorInvestorDemoS3Dir, Error, TEXT("InvestorDemo S3: missing subsystems"));
			bRunning = false;
			EnterPhase(EPhase::Done);
			break;
		}
		const float Half = 600.f;
		const FBox Zone(
			FVector(WorkSiteCenter.X - Half, WorkSiteCenter.Y - Half, WorkSiteCenter.Z - 20000.f),
			FVector(WorkSiteCenter.X + Half, WorkSiteCenter.Y + Half, WorkSiteCenter.Z + 20000.f));
		ProjectId = Projects->CreateProjectFromIntention(
			FName(TEXT("InvestorDemo_S3_CasA")),
			EGardenFervorProjectObjective::WorkSite,
			Zone,
			100);
		if (!ProjectId.IsValid())
		{
			UE_LOG(LogGardenFervorInvestorDemoS3Dir, Error, TEXT("InvestorDemo S3: CreateProjectFromIntention failed"));
			bRunning = false;
			EnterPhase(EPhase::Done);
			break;
		}
		SetLabelText(TEXT("INTENTION"), TEXT("INTENTION\nInvestorDemo_S3_CasA"));
		SetLabelText(TEXT("PROJECT"), FString::Printf(TEXT("PROJECT #%d\nDraft"), ProjectId.Value));
		SetPlaceholderActive(TEXT("PROJECT"), true, FLinearColor(0.65f, 0.35f, 1.f));
		EnterPhase(EPhase::ExpandActivate);
		break;
	}
	case EPhase::ExpandActivate:
	{
		if (PhaseTimer < 0.9f)
		{
			break;
		}
		const int32 Expanded = Projects->ExpandProjectToTasks(ProjectId);
		if (Expanded < 4 || !Projects->ActivateProject(ProjectId))
		{
			UE_LOG(LogGardenFervorInvestorDemoS3Dir, Error,
				TEXT("InvestorDemo S3: expand/activate failed tasks=%d"), Expanded);
			bRunning = false;
			EnterPhase(EPhase::Done);
			break;
		}
		FGardenFervorProjectRecord Project;
		Projects->GetProject(ProjectId, Project);
		if (Project.SitePrep.Mode != EGardenFervorSitePrepMode::AlreadyReady || !Project.bSiteReady)
		{
			UE_LOG(LogGardenFervorInvestorDemoS3Dir, Error, TEXT("InvestorDemo S3: Cas A site not ready"));
			bRunning = false;
			EnterPhase(EPhase::Done);
			break;
		}
		AlignStocksToPhysicalEconomy();
		SetLabelText(TEXT("PROJECT"), FString::Printf(TEXT("PROJECT #%d\nActive"), ProjectId.Value));
		SetLabelText(TEXT("WORKSITE"), TEXT("WORKSITE\nAlreadyReady (Cas A)"));
		SetPlaceholderActive(TEXT("WORKSITE"), true, FLinearColor(0.15f, 0.75f, 0.25f));
		SetPlaceholderActive(TEXT("STOCK_A"), false, FLinearColor(0.55f, 0.35f, 0.15f));
		SetPlaceholderActive(TEXT("STOCK_B"), false, FLinearColor(0.15f, 0.55f, 0.55f));
		SetLabelText(TEXT("STOCK_A"), TEXT("STOCK A\nTimber=0 (live)"));
		SetLabelText(TEXT("STOCK_B"), TEXT("STOCK B\nTimber=0 (live)"));
		EnterPhase(EPhase::SpawnUnits);
		break;
	}
	case EPhase::SpawnUnits:
	{
		if (PhaseTimer < 0.7f)
		{
			break;
		}
		FVector LocU1 = WorkSiteCenter + FVector(-2200.f, 200.f, 100.f);
		FVector LocU2 = WorkSiteCenter + FVector(0.f, 800.f, 100.f);
		FVector LocU3 = WorkSiteCenter + FVector(2200.f, 1200.f, 100.f);
		if (AActor* PH = FindByKey(TEXT("U1")))
		{
			LocU1 = PH->GetActorLocation();
		}
		if (AActor* PH = FindByKey(TEXT("U2")))
		{
			LocU2 = PH->GetActorLocation();
		}
		if (AActor* PH = FindByKey(TEXT("U3")))
		{
			LocU3 = PH->GetActorLocation();
		}

		UnitU1 = SpawnDemoUnit(EGardenFervorCohortUnitRole::U1, LocU1, FLinearColor(1.f, 0.45f, 0.1f));   // orange
		UnitU2 = SpawnDemoUnit(EGardenFervorCohortUnitRole::U2, LocU2, FLinearColor(1.f, 0.9f, 0.15f));  // yellow
		UnitU3 = SpawnDemoUnit(EGardenFervorCohortUnitRole::U3, LocU3, FLinearColor(0.85f, 0.2f, 0.85f)); // magenta
		if (!UnitU1 || !UnitU2 || !UnitU3)
		{
			UE_LOG(LogGardenFervorInvestorDemoS3Dir, Error, TEXT("InvestorDemo S3: unit spawn failed"));
			bRunning = false;
			EnterPhase(EPhase::Done);
			break;
		}
		SetLabelText(TEXT("U1"), TEXT("U1 — EXTRACTION\nactive"));
		SetLabelText(TEXT("U2"), TEXT("U2 — TRANSPORT\nwaiting"));
		SetLabelText(TEXT("U3"), TEXT("U3 — CONSTRUCTION\nwaiting"));
		SetPlaceholderActive(TEXT("U1"), true, FLinearColor(1.f, 0.45f, 0.1f));
		EnterPhase(EPhase::AutonomousRun);
		break;
	}
	case EPhase::AutonomousRun:
	{
		// UnitTaskAgent ticks itself; keep project sync + presentation feedback.
		if (Projects)
		{
			Projects->SyncProjectStatusFromTasks(ProjectId);
		}

		FGardenFervorProjectRecord Project;
		if (Projects && Projects->GetProject(ProjectId, Project) && Eco)
		{
			const float A = GardenFervorGetCohortStockATimberAvailable(Eco, Project);
			const float B = GardenFervorGetCohortStockBTimberAvailableLive(Eco, Project);
			PeakStockA = FMath::Max(PeakStockA, A);

			SetLabelText(TEXT("STOCK_A"),
				FString::Printf(TEXT("STOCK A\nTimber=%.1f (live PE)\nid=%d"), A, GardenFervorCohortStockAId(Project)));
			SetLabelText(TEXT("STOCK_B"),
				FString::Printf(TEXT("STOCK B\nTimber=%.1f (live PE)\nid=%d"), B, GardenFervorCohortStockBId(Project)));
			SetLabelText(TEXT("HUD"), GardenFervorFormatCohortPhysicalEconomySnapshot(Eco, Project));

			if (A > 0.01f)
			{
				SetPlaceholderActive(TEXT("STOCK_A"), true, FLinearColor(0.75f, 0.45f, 0.15f));
				SetLabelText(TEXT("U1"), TEXT("U1 — EXTRACTION\nTimber → A"));
			}
			if (B > 0.01f)
			{
				SetPlaceholderActive(TEXT("STOCK_B"), true, FLinearColor(0.15f, 0.75f, 0.7f));
				SetPlaceholderActive(TEXT("U2"), true, FLinearColor(1.f, 0.9f, 0.15f));
				SetLabelText(TEXT("U2"), TEXT("U2 — TRANSPORT\nA → B"));
			}

			bool bExtractDone = false;
			bool bHaulDone = false;
			bool bBuildDone = false;
			if (Tasks)
			{
				for (const FGardenFervorTaskRecord& T : Tasks->GetTasksForProject(ProjectId))
				{
					if (T.Status != EGardenFervorTaskStatus::Completed)
					{
						continue;
					}
					if (T.TaskType == EGardenFervorTaskType::Extract)
					{
						bExtractDone = true;
					}
					if (T.TaskType == EGardenFervorTaskType::Transport)
					{
						bHaulDone = true;
					}
					if (T.TaskType == EGardenFervorTaskType::Build)
					{
						bBuildDone = true;
					}
				}
			}
			if (bBuildDone || Project.bConstructionComplete)
			{
				SetPlaceholderActive(TEXT("U3"), true, FLinearColor(0.85f, 0.2f, 0.85f));
				SetLabelText(TEXT("U3"), TEXT("U3 — CONSTRUCTION\nAchevé"));
			}

			if (Project.bConstructionComplete && !Project.bInService)
			{
				Projects->RefreshCohortServiceState(ProjectId);
				Projects->GetProject(ProjectId, Project);
			}

			if (Project.bInService)
			{
				SetPlaceholderActive(TEXT("EN_SERVICE"), true, FLinearColor(0.2f, 1.f, 0.35f));
				SetLabelText(TEXT("EN_SERVICE"), TEXT("EN SERVICE\nACTIVE (T7 live)"));
				EnterPhase(EPhase::Finish);
				break;
			}
		}

		if (PhaseTimer > 45.f)
		{
			UE_LOG(LogGardenFervorInvestorDemoS3Dir, Warning, TEXT("InvestorDemo S3: timeout waiting for En service"));
			EnterPhase(EPhase::Finish);
		}
		break;
	}
	case EPhase::Finish:
	{
		FGardenFervorProjectRecord Project;
		float AFinal = 0.f;
		float BFinal = 0.f;
		if (Projects && Projects->GetProject(ProjectId, Project) && Eco)
		{
			Projects->RefreshCohortServiceState(ProjectId);
			Projects->GetProject(ProjectId, Project);
			AFinal = GardenFervorGetCohortStockATimberAvailable(Eco, Project);
			BFinal = GardenFervorGetCohortStockBTimberAvailableLive(Eco, Project);
			SetLabelText(TEXT("HUD"), GardenFervorFormatCohortPhysicalEconomySnapshot(Eco, Project));
			if (Project.bConstructionComplete)
			{
				SetLabelText(TEXT("U3"), TEXT("U3 — CONSTRUCTION\nAchevé (Complete)"));
			}
			if (Project.bInService)
			{
				SetPlaceholderActive(TEXT("EN_SERVICE"), true, FLinearColor(0.2f, 1.f, 0.35f));
				SetLabelText(TEXT("EN_SERVICE"), TEXT("EN SERVICE\nACTIVE (T7 live)"));
			}
		}

		bSucceeded =
			Project.bConstructionComplete
			&& Project.bInService
			&& BFinal >= 0.99f
			&& PeakStockA >= 0.99f
			&& GardenFervorCohortStocksAreDistinct(Project);

		UE_LOG(LogGardenFervorInvestorDemoS3Dir, Display,
			TEXT("InvestorDemo S3 Project #%d ok=%d · PeakA=%.1f A=%.1f B=%.1f · Complete=%d EnService=%d · PE live · CasA no terraform"),
			ProjectId.Value,
			bSucceeded ? 1 : 0,
			PeakStockA,
			AFinal,
			BFinal,
			Project.bConstructionComplete ? 1 : 0,
			Project.bInService ? 1 : 0);

		bRunning = false;
		EnterPhase(EPhase::Done);
		break;
	}
	case EPhase::Idle:
	case EPhase::Done:
	default:
		break;
	}
}
