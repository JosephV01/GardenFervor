// Copyright Epic Games, Inc. All Rights Reserved.

#include "GardenFervorProjectSubsystem.h"

#include "GardenFervorDeveloperSettings.h"
#include "GardenFervorPhysicalEconomySubsystem.h"
#include "GardenFervorRTSCatalog.h"
#include "GardenFervorSitePrepHelpers.h"
#include "GardenFervorTaskSubsystem.h"
#include "GardenFervorUnitBase.h"
#include "GardenFervorUnitDefinition.h"
#include "GardenFervorUnitTaskAgent.h"

#include "EngineUtils.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "HAL/IConsoleManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogGardenFervorProject, Log, All);

void UGardenFervorProjectSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	ClearAll();
}

void UGardenFervorProjectSubsystem::Deinitialize()
{
	ClearAll();
	Super::Deinitialize();
}

void UGardenFervorProjectSubsystem::ClearAll()
{
	Projects.Reset();
	NextProjectId = 1;
	LastSmokeProjectId = FGardenFervorProjectId{};
}

FGardenFervorProjectRecord* UGardenFervorProjectSubsystem::FindMutable(int32 Id)
{
	return Projects.Find(Id);
}

const FGardenFervorProjectRecord* UGardenFervorProjectSubsystem::FindConst(int32 Id) const
{
	return Projects.Find(Id);
}

FGardenFervorProjectId UGardenFervorProjectSubsystem::CreateProject(
	FName DisplayName,
	EGardenFervorProjectObjective Objective,
	const FBox& ZoneBounds,
	int32 Priority)
{
	FGardenFervorProjectRecord Rec;
	Rec.ProjectId.Value = NextProjectId++;
	Rec.DisplayName = DisplayName;
	Rec.Objective = Objective;
	Rec.ZoneBounds = ZoneBounds;
	Rec.Priority = Priority;
	Rec.Status = EGardenFervorProjectStatus::Draft;
	Projects.Add(Rec.ProjectId.Value, Rec);
	return Rec.ProjectId;
}

bool UGardenFervorProjectSubsystem::GetProject(FGardenFervorProjectId ProjectId, FGardenFervorProjectRecord& OutProject) const
{
	const FGardenFervorProjectRecord* Found = FindConst(ProjectId.Value);
	if (!Found)
	{
		return false;
	}
	OutProject = *Found;
	return true;
}

TArray<FGardenFervorProjectRecord> UGardenFervorProjectSubsystem::GetAllProjects() const
{
	TArray<FGardenFervorProjectRecord> Out;
	Projects.GenerateValueArray(Out);
	Out.Sort([](const FGardenFervorProjectRecord& A, const FGardenFervorProjectRecord& B)
	{
		return A.ProjectId.Value < B.ProjectId.Value;
	});
	return Out;
}

int32 UGardenFervorProjectSubsystem::ExpandLevelPad(FGardenFervorProjectRecord& Project, UGardenFervorTaskSubsystem* TaskSys)
{
	UWorld* World = GetWorld();
	UGardenFervorPhysicalEconomySubsystem* Eco = World
		? World->GetSubsystem<UGardenFervorPhysicalEconomySubsystem>()
		: nullptr;

	const FVector PadCenter = Project.ZoneBounds.IsValid
		? Project.ZoneBounds.GetCenter()
		: FVector::ZeroVector;
	// Pit offset so haul is mandatory (not co-located magic).
	const FVector PitCenter = PadCenter + FVector(-2500.f, 0.f, 0.f);

	if (Eco)
	{
		if (Project.LinkedStockId <= 0)
		{
			const FGardenFervorPhysicalStockId PadId = Eco->CreateStock(
				FName(*FString::Printf(TEXT("PadStock_%d"), Project.ProjectId.Value)),
				PadCenter);
			Project.LinkedStockId = PadId.Value;
		}
		if (Project.LinkedPitStockId <= 0)
		{
			const FGardenFervorPhysicalStockId PitId = Eco->CreateStock(
				FName(*FString::Printf(TEXT("PitStock_%d"), Project.ProjectId.Value)),
				PitCenter);
			Project.LinkedPitStockId = PitId.Value;
		}
	}

	const FBox PitBounds(
		PitCenter - FVector(400.f, 400.f, 20000.f),
		PitCenter + FVector(400.f, 400.f, 20000.f));

	auto MakeTask = [&](EGardenFervorTaskType Type, FName Name, const TArray<int32>& Prereqs,
		bool bNeedsFill, const FBox& Area, int32 SourceStock, int32 DestStock)
	{
		FGardenFervorTaskRecord T;
		T.ProjectId = Project.ProjectId;
		T.TaskType = Type;
		T.DisplayName = Name;
		T.PrerequisiteTaskIds = Prereqs;
		T.AreaBounds = Area;
		T.Priority = Project.Priority;
		T.Status = EGardenFervorTaskStatus::Pending;
		T.SourceStockId = SourceStock;
		T.DestStockId = DestStock;
		if (Type == EGardenFervorTaskType::Terraform)
		{
			T.RequiredCapabilities.Add(FName(TEXT("Terraform")));
		}
		else
		{
			T.RequiredCapabilities.Add(FName(TEXT("Worker")));
		}
		if (bNeedsFill)
		{
			T.Reservation.ResourceKey = FName(TEXT("FillDirt"));
			T.Reservation.Amount = 10.f;
			T.Reservation.bExclusive = true;
			T.Reservation.StockId = Project.LinkedStockId;
		}
		const FGardenFervorTaskId Id = TaskSys->CreateTask(T);
		Project.TaskIds.Add(Id.Value);
		return Id.Value;
	};

	// Pit extract → haul to pad → transform → raise consume (F6+F7).
	const int32 AnalyzeId = MakeTask(EGardenFervorTaskType::Analyze, FName(TEXT("AnalyzeTerrain")), {},
		false, Project.ZoneBounds, 0, 0);
	const int32 PrepareId = MakeTask(EGardenFervorTaskType::Prepare, FName(TEXT("PrepareSite")), {AnalyzeId},
		false, Project.ZoneBounds, 0, 0);
	const int32 ExtractId = MakeTask(EGardenFervorTaskType::Extract, FName(TEXT("ExtractSpoil")), {PrepareId},
		false, PitBounds, Project.LinkedPitStockId, 0);
	const int32 HaulId = MakeTask(EGardenFervorTaskType::Transport, FName(TEXT("HaulSpoil")), {ExtractId},
		false, Project.ZoneBounds, Project.LinkedPitStockId, Project.LinkedStockId);
	const int32 TransformId = MakeTask(EGardenFervorTaskType::Build, FName(TEXT("TransformFill")), {HaulId},
		false, Project.ZoneBounds, 0, Project.LinkedStockId);
	const int32 RaiseId = MakeTask(EGardenFervorTaskType::Terraform, FName(TEXT("RaiseGrade")), {TransformId},
		true, Project.ZoneBounds, 0, 0);
	MakeTask(EGardenFervorTaskType::Verify, FName(TEXT("VerifyResult")), {RaiseId},
		false, Project.ZoneBounds, 0, 0);

	TaskSys->RefreshReadiness(Project.ProjectId);
	return Project.TaskIds.Num();
}

int32 UGardenFervorProjectSubsystem::ExpandWorkSite(
	FGardenFervorProjectRecord& Project, UGardenFervorTaskSubsystem* TaskSys)
{
	UWorld* World = GetWorld();
	UGardenFervorPhysicalEconomySubsystem* Eco = World
		? World->GetSubsystem<UGardenFervorPhysicalEconomySubsystem>()
		: nullptr;

	// Default cohort Cas A if unset.
	if (Project.SitePrep.Mode == EGardenFervorSitePrepMode::None)
	{
		Project.SitePrep.Mode = EGardenFervorSitePrepMode::AlreadyReady;
		Project.SitePrep.bRequestTerrainModify = false;
	}

	FGardenFervorSitePrepResult PrepResult;
	if (!GardenFervorApplySitePreparation(Eco, Project, PrepResult) || !PrepResult.bSiteReady)
	{
		Project.BlockReason = PrepResult.Detail;
		Project.Status = EGardenFervorProjectStatus::Blocked;
		UE_LOG(LogGardenFervorProject, Warning, TEXT("WorkSite prep failed for project %d: %s"),
			Project.ProjectId.Value, *PrepResult.Detail);
		return 0;
	}

	Project.BlockReason.Reset();
	// T5 Cas A foundation only: site ready + stocks A/B. No Terraform / Spoil / Extract-Transport-Build.
	if (TaskSys)
	{
		TaskSys->RefreshReadiness(Project.ProjectId);
	}
	UE_LOG(LogGardenFervorProject, Log,
		TEXT("WorkSite Cas A ready project %d — StockA=%d StockB=%d (no terraform)"),
		Project.ProjectId.Value, Project.LinkedPitStockId, Project.LinkedStockId);
	return Project.TaskIds.Num();
}

int32 UGardenFervorProjectSubsystem::ExpandProjectToTasks(FGardenFervorProjectId ProjectId)
{
	FGardenFervorProjectRecord* Project = FindMutable(ProjectId.Value);
	UWorld* World = GetWorld();
	UGardenFervorTaskSubsystem* TaskSys = World ? World->GetSubsystem<UGardenFervorTaskSubsystem>() : nullptr;
	if (!Project || !TaskSys)
	{
		return 0;
	}
	if (Project->TaskIds.Num() > 0)
	{
		return Project->TaskIds.Num();
	}

	int32 Count = 0;
	switch (Project->Objective)
	{
	case EGardenFervorProjectObjective::LevelPad:
		Count = ExpandLevelPad(*Project, TaskSys);
		break;
	case EGardenFervorProjectObjective::WorkSite:
		Count = ExpandWorkSite(*Project, TaskSys);
		break;
	case EGardenFervorProjectObjective::SurveyOnly:
	{
		FGardenFervorTaskRecord T;
		T.ProjectId = Project->ProjectId;
		T.TaskType = EGardenFervorTaskType::Analyze;
		T.DisplayName = FName(TEXT("SurveyZone"));
		T.AreaBounds = Project->ZoneBounds;
		T.Priority = Project->Priority;
		const FGardenFervorTaskId Id = TaskSys->CreateTask(T);
		Project->TaskIds.Add(Id.Value);
		TaskSys->RefreshReadiness(Project->ProjectId);
		Count = 1;
		break;
	}
	default:
		UE_LOG(LogGardenFervorProject, Warning, TEXT("No planner for objective"));
		return 0;
	}

	if (Project->Status != EGardenFervorProjectStatus::Blocked)
	{
		Project->Status = EGardenFervorProjectStatus::Ready;
	}
	UE_LOG(LogGardenFervorProject, Log, TEXT("Expanded project %d '%s' into %d tasks"),
		Project->ProjectId.Value, *Project->DisplayName.ToString(), Count);
	return Count;
}

bool UGardenFervorProjectSubsystem::ActivateProject(FGardenFervorProjectId ProjectId)
{
	FGardenFervorProjectRecord* Project = FindMutable(ProjectId.Value);
	if (!Project)
	{
		return false;
	}
	if (Project->TaskIds.Num() == 0)
	{
		ExpandProjectToTasks(ProjectId);
	}
	if (Project->TaskIds.Num() == 0)
	{
		return false;
	}
	Project->Status = EGardenFervorProjectStatus::Running;
	Project->BlockReason.Reset();
	if (UWorld* World = GetWorld())
	{
		if (UGardenFervorTaskSubsystem* TaskSys = World->GetSubsystem<UGardenFervorTaskSubsystem>())
		{
			TaskSys->RefreshReadiness(ProjectId);
		}
	}
	return true;
}

void UGardenFervorProjectSubsystem::SyncProjectStatusFromTasks(FGardenFervorProjectId ProjectId)
{
	FGardenFervorProjectRecord* Project = FindMutable(ProjectId.Value);
	UWorld* World = GetWorld();
	UGardenFervorTaskSubsystem* TaskSys = World ? World->GetSubsystem<UGardenFervorTaskSubsystem>() : nullptr;
	if (!Project || !TaskSys || Project->TaskIds.Num() == 0)
	{
		return;
	}

	int32 Completed = 0;
	int32 Failed = 0;
	int32 BlockedUseful = 0;
	FString FirstBlock;
	for (const int32 Tid : Project->TaskIds)
	{
		FGardenFervorTaskRecord Task;
		if (!TaskSys->GetTask(FGardenFervorTaskId{Tid}, Task))
		{
			continue;
		}
		if (Task.Status == EGardenFervorTaskStatus::Completed)
		{
			++Completed;
		}
		else if (Task.Status == EGardenFervorTaskStatus::Failed)
		{
			++Failed;
		}
		else if (Task.Status == EGardenFervorTaskStatus::Blocked
			&& Task.BlockCause != EGardenFervorTaskBlockCause::WaitingPrerequisites)
		{
			++BlockedUseful;
			if (FirstBlock.IsEmpty())
			{
				FirstBlock = TaskSys->GetPrimaryFailureReason(Task.TaskId);
			}
		}
	}

	if (Failed > 0)
	{
		Project->Status = EGardenFervorProjectStatus::Failed;
		Project->BlockReason = FirstBlock;
	}
	else if (Completed == Project->TaskIds.Num())
	{
		Project->Status = EGardenFervorProjectStatus::Completed;
		Project->BlockReason.Reset();
	}
	else if (BlockedUseful > 0)
	{
		Project->Status = EGardenFervorProjectStatus::Blocked;
		Project->BlockReason = FirstBlock;
	}
	else if (Project->Status != EGardenFervorProjectStatus::Draft)
	{
		Project->Status = EGardenFervorProjectStatus::Running;
	}
}

FGardenFervorProjectId UGardenFervorProjectSubsystem::SmokeStartLevelPadNear(
	FVector Center,
	FString& OutMessage,
	bool bEnsureUnits,
	float HalfExtentXY)
{
	OutMessage.Reset();
	UWorld* World = GetWorld();
	UGardenFervorTaskSubsystem* Tasks = World ? World->GetSubsystem<UGardenFervorTaskSubsystem>() : nullptr;
	if (!World || !Tasks)
	{
		OutMessage = TEXT("LevelPad smoke: no world/tasks");
		return FGardenFervorProjectId{};
	}

	HalfExtentXY = FMath::Max(200.f, HalfExtentXY);
	const FBox Zone(
		FVector(Center.X - HalfExtentXY, Center.Y - HalfExtentXY, Center.Z - 20000.f),
		FVector(Center.X + HalfExtentXY, Center.Y + HalfExtentXY, Center.Z + 20000.f));

	const FGardenFervorProjectId ProjectId = CreateProject(
		FName(TEXT("Dev_LevelPad")),
		EGardenFervorProjectObjective::LevelPad,
		Zone,
		50);
	if (!ProjectId.IsValid())
	{
		OutMessage = TEXT("LevelPad smoke: create failed");
		return FGardenFervorProjectId{};
	}

	const int32 Expanded = ExpandProjectToTasks(ProjectId);
	if (Expanded < 7 || !ActivateProject(ProjectId))
	{
		OutMessage = FString::Printf(TEXT("LevelPad smoke: expand/activate failed (tasks=%d)"), Expanded);
		return FGardenFervorProjectId{};
	}

	// No magic FillDirt seed — Extract→Haul→Transform must feed Raise (F6/F7).
	LastSmokeProjectId = ProjectId;

	int32 Workers = 0;
	int32 Terraformers = 0;
	for (TActorIterator<AGardenFervorUnitBase> It(World); It; ++It)
	{
		AGardenFervorUnitBase* Unit = *It;
		if (!IsValid(Unit))
		{
			continue;
		}
		if (Unit->IsTerraformer())
		{
			++Terraformers;
		}
		else if (Unit->IsWorker())
		{
			++Workers;
		}
		if (UGardenFervorUnitTaskAgent* Agent = Unit->GetTaskAgent())
		{
			Agent->SetAutonomyEnabled(true);
			Agent->SetInstantMode(false);
			Agent->SetProjectFilter(ProjectId);
		}
	}

	if (bEnsureUnits)
	{
		const UGardenFervorDeveloperSettings* Settings = UGardenFervorDeveloperSettings::Get();
		const UGardenFervorRTSCatalog* Catalog = Settings ? Settings->LoadRTSCatalog() : nullptr;
		auto SpawnRole = [&](FName UnitId, const FVector& Offset) -> AGardenFervorUnitBase*
		{
			UGardenFervorUnitDefinition* Def = Catalog ? Catalog->FindUnitById(UnitId) : nullptr;
			UClass* UnitClass = (Def && Def->UnitClass) ? Def->UnitClass.Get() : AGardenFervorUnitBase::StaticClass();
			FActorSpawnParameters Params;
			Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AGardenFervorUnitBase* Unit = World->SpawnActor<AGardenFervorUnitBase>(
				UnitClass, Center + Offset, FRotator::ZeroRotator, Params);
			if (!Unit)
			{
				return nullptr;
			}
			if (Def)
			{
				Unit->ApplyDefinition(Def);
			}
			else
			{
				UGardenFervorUnitDefinition* Transient = NewObject<UGardenFervorUnitDefinition>(Unit);
				Transient->UnitId = UnitId;
				Transient->DisplayName = FText::FromName(UnitId);
				Transient->bIsWorker = (UnitId == FName(TEXT("Worker")));
				Transient->Capabilities = {
					UnitId == FName(TEXT("Terraformer")) ? FName(TEXT("Terraform")) : FName(TEXT("Worker"))
				};
				Unit->ApplyDefinition(Transient);
			}
			Unit->SnapToGroundAt(Center + Offset);
			if (UGardenFervorUnitTaskAgent* Agent = Unit->GetTaskAgent())
			{
				Agent->SetAutonomyEnabled(true);
				Agent->SetInstantMode(false);
				Agent->SetProjectFilter(ProjectId);
			}
			Unit->PulseSpawnBeacon(8.f);
			return Unit;
		};

		if (Workers == 0 && SpawnRole(FName(TEXT("Worker")), FVector(-350.f, -200.f, 0.f)))
		{
			++Workers;
		}
		if (Terraformers == 0 && SpawnRole(FName(TEXT("Terraformer")), FVector(-350.f, 200.f, 0.f)))
		{
			++Terraformers;
		}
	}

	OutMessage = FString::Printf(
		TEXT("LevelPad #%d Running · Pit→Haul→Pad Spoil→Fill→Raise · units W=%d T=%d"),
		ProjectId.Value, Workers, Terraformers);
	UE_LOG(LogGardenFervorProject, Log, TEXT("%s"), *OutMessage);
	return ProjectId;
}

FString UGardenFervorProjectSubsystem::GetSmokeStatusLine() const
{
	if (!LastSmokeProjectId.IsValid())
	{
		return TEXT("LevelPad: none (click Start LevelPad)");
	}

	FGardenFervorProjectRecord Project;
	if (!GetProject(LastSmokeProjectId, Project))
	{
		return TEXT("LevelPad: missing");
	}

	UWorld* World = GetWorld();
	UGardenFervorTaskSubsystem* Tasks = World ? World->GetSubsystem<UGardenFervorTaskSubsystem>() : nullptr;
	int32 Done = 0;
	int32 Total = Project.TaskIds.Num();
	FString ActiveName;
	if (Tasks)
	{
		for (const int32 Tid : Project.TaskIds)
		{
			FGardenFervorTaskRecord Task;
			if (!Tasks->GetTask(FGardenFervorTaskId{Tid}, Task))
			{
				continue;
			}
			if (Task.Status == EGardenFervorTaskStatus::Completed)
			{
				++Done;
			}
			else if (ActiveName.IsEmpty()
				&& (Task.Status == EGardenFervorTaskStatus::Running
					|| Task.Status == EGardenFervorTaskStatus::Reserved
					|| Task.Status == EGardenFervorTaskStatus::Ready))
			{
				ActiveName = Task.DisplayName.ToString();
			}
		}
	}

	const TCHAR* StatusName = TEXT("?");
	switch (Project.Status)
	{
	case EGardenFervorProjectStatus::Running: StatusName = TEXT("Running"); break;
	case EGardenFervorProjectStatus::Completed: StatusName = TEXT("Completed"); break;
	case EGardenFervorProjectStatus::Blocked: StatusName = TEXT("Blocked"); break;
	case EGardenFervorProjectStatus::Failed: StatusName = TEXT("Failed"); break;
	default: StatusName = TEXT("Other"); break;
	}

	if (Project.Status == EGardenFervorProjectStatus::Completed)
	{
		return FString::Printf(TEXT("LevelPad #%d Completed (%d/%d)"), Project.ProjectId.Value, Done, Total);
	}

	FString StockLine;
	if (Project.LinkedStockId > 0 || Project.LinkedPitStockId > 0)
	{
		if (UGardenFervorPhysicalEconomySubsystem* Eco =
			World ? World->GetSubsystem<UGardenFervorPhysicalEconomySubsystem>() : nullptr)
		{
			FGardenFervorPhysicalStockId PadId;
			PadId.Value = Project.LinkedStockId;
			FGardenFervorPhysicalStockId PitId;
			PitId.Value = Project.LinkedPitStockId;
			StockLine = FString::Printf(TEXT(" · PitSpoil=%.0f PadSpoil=%.0f Fill=%.0f"),
				Eco->GetAvailable(PitId, FName(TEXT("SpoilDirt"))),
				Eco->GetAvailable(PadId, FName(TEXT("SpoilDirt"))),
				Eco->GetAvailable(PadId, FName(TEXT("FillDirt"))));
		}
	}

	if (!ActiveName.IsEmpty())
	{
		return FString::Printf(TEXT("LevelPad #%d %s · %d/%d · now %s%s"),
			Project.ProjectId.Value, StatusName, Done, Total, *ActiveName, *StockLine);
	}
	return FString::Printf(TEXT("LevelPad #%d %s · %d/%d%s"),
		Project.ProjectId.Value, StatusName, Done, Total, *StockLine);
}

static FAutoConsoleCommandWithWorld GGardenFervorProjectSmokeLevelPadCmd(
	TEXT("gf.Project.SmokeLevelPad"),
	TEXT("Provisional: create/activate LevelPad near player; physical Spoil→Fill→Raise; ensure Worker+Terraformer"),
	FConsoleCommandWithWorldDelegate::CreateLambda([](UWorld* World)
	{
		if (!World)
		{
			UE_LOG(LogGardenFervorProject, Warning, TEXT("gf.Project.SmokeLevelPad: no world"));
			return;
		}
		UGardenFervorProjectSubsystem* Projects = World->GetSubsystem<UGardenFervorProjectSubsystem>();
		if (!Projects)
		{
			UE_LOG(LogGardenFervorProject, Warning, TEXT("gf.Project.SmokeLevelPad: no ProjectSubsystem"));
			return;
		}

		FVector Center = FVector::ZeroVector;
		if (APlayerController* PC = World->GetFirstPlayerController())
		{
			if (APawn* Pawn = PC->GetPawn())
			{
				Center = Pawn->GetActorLocation();
			}
			else
			{
				FVector CamLoc = FVector::ZeroVector;
				FRotator CamRot = FRotator::ZeroRotator;
				PC->GetPlayerViewPoint(CamLoc, CamRot);
				Center = CamLoc + CamRot.Vector() * 1500.f;
				Center.Z = CamLoc.Z;
			}
		}

		FString Msg;
		Projects->SmokeStartLevelPadNear(Center, Msg, true, 600.f);
	}));

