// Copyright Epic Games, Inc. All Rights Reserved.

#include "GardenFervorInvestorDemoS3Director.h"

#include "GardenFervorCohortObservabilityHelpers.h"
#include "GardenFervorCohortStockHelpers.h"
#include "GardenFervorInvestorDemoPresentationWidget.h"
#include "GardenFervorPhysicalEconomySubsystem.h"
#include "GardenFervorPhysicalResourceTypes.h"
#include "GardenFervorProjectSubsystem.h"
#include "GardenFervorSitePrepTypes.h"
#include "GardenFervorStrategyPawn.h"
#include "GardenFervorTaskSubsystem.h"
#include "GardenFervorTaskTypes.h"
#include "GardenFervorUnitBase.h"
#include "GardenFervorUnitDefinition.h"
#include "GardenFervorUnitTaskAgent.h"
#include "Blueprint/UserWidget.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/TextRenderActor.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
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

	static constexpr int32 PresentationStepCount = 10;
	static constexpr float HoldIntention = 1.15f;
	static constexpr float HoldProject = 1.25f;
	static constexpr float HoldAnalyse = 1.15f;
	static constexpr float HoldWorkSite = 1.25f;
	static constexpr float HoldSpawn = 0.85f;
	static constexpr float HoldConclusion = 3.6f;

	static bool NameMatchesKey(const FString& Name, const FName& Key)
	{
		const FString K = Key.ToString();
		if (Name.Contains(K, ESearchCase::IgnoreCase))
		{
			return true;
		}
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
	bCreateProjectApiDone = false;
	bExpandApiDone = false;
	bFinishLogged = false;
	bDriveCamera = true;
	PresentationBeat = EPresentationBeat::Idle;
	PresentationDetail.Reset();
	EnsurePresentationWidget();
	EnterPhase(EPhase::BootLayout);
	UE_LOG(LogGardenFervorInvestorDemoS3Dir, Display,
		TEXT("InvestorDemo S3 presentation started (async · étape4 camera/UI)"));
}

void AGardenFervorInvestorDemoS3Director::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	TearDownPresentationWidget();
	Super::EndPlay(EndPlayReason);
}

void AGardenFervorInvestorDemoS3Director::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (bRunning)
	{
		Advance(DeltaSeconds);
	}
	UpdateCamera(DeltaSeconds);
	FaceLabelsToCamera();
	RefreshPresentationWidget();
}

void AGardenFervorInvestorDemoS3Director::EnterPhase(EPhase NewPhase)
{
	Phase = NewPhase;
	PhaseTimer = 0.f;
}

void AGardenFervorInvestorDemoS3Director::GetBeatMeta(
	EPresentationBeat Beat, int32& OutStep, FString& OutTitle)
{
	switch (Beat)
	{
	case EPresentationBeat::Intention: OutStep = 1; OutTitle = TEXT("Intention"); break;
	case EPresentationBeat::Project: OutStep = 2; OutTitle = TEXT("Projet"); break;
	case EPresentationBeat::Analyse: OutStep = 3; OutTitle = TEXT("Analyse"); break;
	case EPresentationBeat::WorkSite: OutStep = 4; OutTitle = TEXT("WorkSite"); break;
	case EPresentationBeat::Extraction: OutStep = 5; OutTitle = TEXT("Extraction"); break;
	case EPresentationBeat::Transport: OutStep = 6; OutTitle = TEXT("Transport"); break;
	case EPresentationBeat::StockB: OutStep = 7; OutTitle = TEXT("Stock B"); break;
	case EPresentationBeat::Construction: OutStep = 8; OutTitle = TEXT("Construction"); break;
	case EPresentationBeat::Acheve: OutStep = 9; OutTitle = TEXT("Achevé"); break;
	case EPresentationBeat::EnService:
	case EPresentationBeat::Conclusion: OutStep = 10; OutTitle = TEXT("En service"); break;
	default: OutStep = 0; OutTitle = TEXT("…"); break;
	}
}

void AGardenFervorInvestorDemoS3Director::SetPresentationBeat(
	EPresentationBeat NewBeat, const FString& Detail)
{
	PresentationBeat = NewBeat;
	PresentationDetail = Detail;
}

void AGardenFervorInvestorDemoS3Director::SetCameraFocus(const FVector& WorldXY, float ArmLength)
{
	CameraFocusXY = WorldXY;
	CameraArmLength = ArmLength;
	bDriveCamera = true;
}

void AGardenFervorInvestorDemoS3Director::UpdateCamera(float DeltaSeconds)
{
	if (!bDriveCamera)
	{
		return;
	}
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	APlayerController* PC = World->GetFirstPlayerController();
	if (!PC)
	{
		return;
	}
	AGardenFervorStrategyPawn* Pawn = Cast<AGardenFervorStrategyPawn>(PC->GetPawn());
	if (!Pawn)
	{
		return;
	}

	FVector Ground = CameraFocusXY;
	SampleLandscape(CameraFocusXY, Ground);
	const FVector Desired(Ground.X, Ground.Y, Ground.Z + 80.f);
	const FVector Cur = Pawn->GetActorLocation();
	Pawn->SetActorLocation(FMath::VInterpTo(Cur, Desired, DeltaSeconds, 2.4f));

	if (USpringArmComponent* Boom = Pawn->GetCameraBoom())
	{
		Boom->TargetArmLength = FMath::FInterpTo(Boom->TargetArmLength, CameraArmLength, DeltaSeconds, 2.0f);
		const FRotator CurRot = Boom->GetRelativeRotation();
		const FRotator DesiredRot(-52.f, CurRot.Yaw, 0.f);
		Boom->SetRelativeRotation(FMath::RInterpTo(CurRot, DesiredRot, DeltaSeconds, 1.8f));
	}
}

void AGardenFervorInvestorDemoS3Director::EnsurePresentationWidget()
{
	if (PresentationWidget)
	{
		return;
	}
	UWorld* World = GetWorld();
	APlayerController* PC = World ? World->GetFirstPlayerController() : nullptr;
	if (!PC)
	{
		return;
	}
	PresentationWidget = CreateWidget<UGardenFervorInvestorDemoPresentationWidget>(
		PC, UGardenFervorInvestorDemoPresentationWidget::StaticClass());
	if (PresentationWidget)
	{
		PresentationWidget->AddToViewport(50);
	}
}

void AGardenFervorInvestorDemoS3Director::TearDownPresentationWidget()
{
	if (PresentationWidget)
	{
		PresentationWidget->RemoveFromParent();
		PresentationWidget = nullptr;
	}
}

void AGardenFervorInvestorDemoS3Director::RefreshPresentationWidget()
{
	if (!PresentationWidget)
	{
		return;
	}

	int32 Step = 0;
	FString Title;
	GetBeatMeta(PresentationBeat, Step, Title);

	FString PeLine = TEXT("PE — en attente");
	UWorld* World = GetWorld();
	if (World && ProjectId.IsValid())
	{
		if (UGardenFervorProjectSubsystem* Projects = World->GetSubsystem<UGardenFervorProjectSubsystem>())
		{
			if (UGardenFervorPhysicalEconomySubsystem* Eco = World->GetSubsystem<UGardenFervorPhysicalEconomySubsystem>())
			{
				FGardenFervorProjectRecord Project;
				if (Projects->GetProject(ProjectId, Project))
				{
					const float A = GardenFervorGetCohortStockATimberAvailable(Eco, Project);
					const float B = GardenFervorGetCohortStockBTimberAvailableLive(Eco, Project);
					PeLine = FString::Printf(
						TEXT("A=%.1f  B=%.1f  C=%d  S=%d"),
						A, B,
						Project.bConstructionComplete ? 1 : 0,
						Project.bInService ? 1 : 0);
				}
			}
		}
	}

	const bool bConcluded =
		PresentationBeat == EPresentationBeat::Conclusion
		|| (Phase == EPhase::Done && bFinishLogged);
	PresentationWidget->SetPresentationState(
		Step,
		InvestorDemoS3DirPrivate::PresentationStepCount,
		Title,
		PresentationDetail.IsEmpty() ? TEXT(" ") : PresentationDetail,
		PeLine,
		bConcluded,
		bSucceeded);
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
		Agent->SetInstantMode(false);
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
		SetCameraFocus(WorkSiteCenter + FVector(0.f, -1400.f, 0.f), 3400.f);
		SetPresentationBeat(EPresentationBeat::Intention,
			TEXT("Le joueur formule une intention — site Case A déjà prêt."));
		EnsurePresentationWidget();
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

		if (!bCreateProjectApiDone)
		{
			if (AActor* Intention = FindByKey(TEXT("INTENTION")))
			{
				SetCameraFocus(Intention->GetActorLocation(), 2600.f);
			}
			else
			{
				SetCameraFocus(WorkSiteCenter + FVector(0.f, -2800.f, 0.f), 2600.f);
			}
			SetPresentationBeat(EPresentationBeat::Intention,
				TEXT("Intention visible — création du projet à l'instant suivant."));

			if (PhaseTimer < HoldIntention)
			{
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
			bCreateProjectApiDone = true;
			PhaseTimer = 0.f;
			SetLabelText(TEXT("INTENTION"), TEXT("INTENTION\nInvestorDemo_S3_CasA"));
			SetLabelText(TEXT("PROJECT"), FString::Printf(TEXT("PROJECT #%d\nDraft"), ProjectId.Value));
			SetPlaceholderActive(TEXT("PROJECT"), true, FLinearColor(0.65f, 0.35f, 1.f));
			SetPresentationBeat(EPresentationBeat::Project,
				FString::Printf(TEXT("Projet #%d créé (Draft) via CreateProjectFromIntention."), ProjectId.Value));
			if (AActor* ProjectPH = FindByKey(TEXT("PROJECT")))
			{
				SetCameraFocus(ProjectPH->GetActorLocation(), 2500.f);
			}
			break;
		}

		if (PhaseTimer < HoldProject)
		{
			break;
		}
		EnterPhase(EPhase::ExpandActivate);
		break;
	}
	case EPhase::ExpandActivate:
	{
		if (!bExpandApiDone)
		{
			SetPresentationBeat(EPresentationBeat::Analyse,
				TEXT("Analyse de site (tâche Analyze réelle) — pas de ForestAnalysis."));
			SetLabelText(TEXT("WORKSITE"), TEXT("WORKSITE\nAnalyse…"));
			SetCameraFocus(WorkSiteCenter, 2800.f);

			if (PhaseTimer < HoldAnalyse)
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
			bExpandApiDone = true;
			PhaseTimer = 0.f;
			SetLabelText(TEXT("PROJECT"), FString::Printf(TEXT("PROJECT #%d\nActive"), ProjectId.Value));
			SetLabelText(TEXT("WORKSITE"), TEXT("WORKSITE\nAlreadyReady (Cas A)"));
			SetPlaceholderActive(TEXT("WORKSITE"), true, FLinearColor(0.15f, 0.75f, 0.25f));
			SetPlaceholderActive(TEXT("STOCK_A"), false, FLinearColor(0.55f, 0.35f, 0.15f));
			SetPlaceholderActive(TEXT("STOCK_B"), false, FLinearColor(0.15f, 0.55f, 0.55f));
			SetLabelText(TEXT("STOCK_A"), TEXT("STOCK A\nTimber=0 (live)"));
			SetLabelText(TEXT("STOCK_B"), TEXT("STOCK B\nTimber=0 (live)"));
			SetPresentationBeat(EPresentationBeat::WorkSite,
				TEXT("WorkSite AlreadyReady — Case A · aucun Raise/Lower/Paint."));
			break;
		}

		if (PhaseTimer < HoldWorkSite)
		{
			break;
		}
		EnterPhase(EPhase::SpawnUnits);
		break;
	}
	case EPhase::SpawnUnits:
	{
		if (PhaseTimer < HoldSpawn)
		{
			SetPresentationBeat(EPresentationBeat::Extraction,
				TEXT("Roster U1 / U2 / U3 — Extraction · Transport · Construction."));
			SetCameraFocus(WorkSiteCenter + FVector(-800.f, 400.f, 0.f), 3000.f);
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

		UnitU1 = SpawnDemoUnit(EGardenFervorCohortUnitRole::U1, LocU1, FLinearColor(1.f, 0.45f, 0.1f));
		UnitU2 = SpawnDemoUnit(EGardenFervorCohortUnitRole::U2, LocU2, FLinearColor(1.f, 0.9f, 0.15f));
		UnitU3 = SpawnDemoUnit(EGardenFervorCohortUnitRole::U3, LocU3, FLinearColor(0.85f, 0.2f, 0.85f));
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
		SetPresentationBeat(EPresentationBeat::Extraction,
			TEXT("U1 extrait Timber vers Stock A (PE live)."));
		SetCameraFocus(LocU1, 2400.f);
		EnterPhase(EPhase::AutonomousRun);
		break;
	}
	case EPhase::AutonomousRun:
	{
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

			bool bAnalyzeDone = false;
			bool bAnalyzeActive = false;
			bool bExtractDone = false;
			bool bExtractActive = false;
			bool bHaulDone = false;
			bool bHaulActive = false;
			bool bBuildDone = false;
			bool bBuildActive = false;
			if (Tasks)
			{
				for (const FGardenFervorTaskRecord& T : Tasks->GetTasksForProject(ProjectId))
				{
					const bool bDone = T.Status == EGardenFervorTaskStatus::Completed;
					const bool bActive = T.Status == EGardenFervorTaskStatus::Running
						|| T.Status == EGardenFervorTaskStatus::Reserved
						|| T.Status == EGardenFervorTaskStatus::Ready;
					if (T.TaskType == EGardenFervorTaskType::Analyze)
					{
						bAnalyzeDone |= bDone;
						bAnalyzeActive |= bActive;
					}
					if (T.TaskType == EGardenFervorTaskType::Extract)
					{
						bExtractDone |= bDone;
						bExtractActive |= bActive;
					}
					if (T.TaskType == EGardenFervorTaskType::Transport)
					{
						bHaulDone |= bDone;
						bHaulActive |= bActive;
					}
					if (T.TaskType == EGardenFervorTaskType::Build)
					{
						bBuildDone |= bDone;
						bBuildActive |= bActive;
					}
				}
			}

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
			if (bBuildDone || Project.bConstructionComplete || bBuildActive)
			{
				SetPlaceholderActive(TEXT("U3"), true, FLinearColor(0.85f, 0.2f, 0.85f));
				SetLabelText(TEXT("U3"),
					Project.bConstructionComplete
						? TEXT("U3 — CONSTRUCTION\nAchevé")
						: TEXT("U3 — CONSTRUCTION\nen cours"));
			}

			// Beats from real state only (highest priority last).
			if (!bAnalyzeDone && (bAnalyzeActive || !bExtractActive))
			{
				SetPresentationBeat(EPresentationBeat::Analyse,
					TEXT("Analyse en cours (tâche Analyze réelle)."));
				SetCameraFocus(WorkSiteCenter, 2700.f);
			}
			if (bAnalyzeDone && !bExtractDone && A < 0.01f && !bExtractActive)
			{
				SetPresentationBeat(EPresentationBeat::WorkSite,
					TEXT("WorkSite AlreadyReady — extraction imminente."));
				SetCameraFocus(WorkSiteCenter, 2800.f);
			}
			if (bExtractActive || A > 0.01f || bExtractDone)
			{
				SetPresentationBeat(EPresentationBeat::Extraction,
					TEXT("U1 Extraction Timber → Stock A (Deposit PE)."));
				const FVector Focus = UnitU1 ? UnitU1->GetActorLocation()
					: (FindByKey(TEXT("STOCK_A")) ? FindByKey(TEXT("STOCK_A"))->GetActorLocation()
						: WorkSiteCenter + FVector(-1500.f, 0.f, 0.f));
				SetCameraFocus(Focus, 2300.f);
			}
			if (bHaulActive || (A < PeakStockA - 0.01f && PeakStockA > 0.01f && B < 0.01f))
			{
				SetPresentationBeat(EPresentationBeat::Transport,
					TEXT("U2 Transport réel Stock A → Stock B (Withdraw / cargo / Deposit)."));
				const FVector Focus = UnitU2 ? UnitU2->GetActorLocation() : WorkSiteCenter;
				SetCameraFocus(Focus, 2400.f);
			}
			if (B > 0.01f)
			{
				SetPresentationBeat(EPresentationBeat::StockB,
					TEXT("Stock B Timber > 0 — PE GetAvailable live."));
				if (AActor* StockB = FindByKey(TEXT("STOCK_B")))
				{
					SetCameraFocus(StockB->GetActorLocation(), 2300.f);
				}
			}
			if (bBuildActive || (bHaulDone && !Project.bConstructionComplete))
			{
				SetPresentationBeat(EPresentationBeat::Construction,
					TEXT("U3 Construction sur le WorkSite."));
				const FVector Focus = UnitU3 ? UnitU3->GetActorLocation() : WorkSiteCenter + FVector(2200.f, 1200.f, 0.f);
				SetCameraFocus(Focus, 2400.f);
			}
			if (Project.bConstructionComplete && !Project.bInService)
			{
				SetPresentationBeat(EPresentationBeat::Acheve,
					TEXT("Achevé (Complete) — distinct de En service."));
				SetLabelText(TEXT("U3"), TEXT("U3 — CONSTRUCTION\nAchevé (Complete)"));
				SetCameraFocus(WorkSiteCenter + FVector(1800.f, 1600.f, 0.f), 2600.f);
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
				SetPresentationBeat(EPresentationBeat::EnService,
					TEXT("En service — Complete + Stock B Timber > 0 (T7 live)."));
				EnterPhase(EPhase::Finish);
				break;
			}
		}

		if (PhaseTimer > 55.f)
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

		if (!bFinishLogged)
		{
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

			bFinishLogged = true;
			PhaseTimer = 0.f;
			SetCameraFocus(WorkSiteCenter + FVector(200.f, 400.f, 0.f), 3800.f);
			SetPresentationBeat(EPresentationBeat::Conclusion,
				bSucceeded
					? TEXT("Conclusion — preuve S3 Cas A lisible · PE live · aucun Terraform.")
					: TEXT("Conclusion — parcours incomplet · voir log ok=."));
		}

		if (PhaseTimer < HoldConclusion)
		{
			break;
		}

		bRunning = false;
		bDriveCamera = false;
		EnterPhase(EPhase::Done);
		break;
	}
	case EPhase::Idle:
	case EPhase::Done:
	default:
		break;
	}
}
