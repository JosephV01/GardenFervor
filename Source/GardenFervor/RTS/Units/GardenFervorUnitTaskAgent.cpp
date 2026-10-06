// Copyright Epic Games, Inc. All Rights Reserved.

#include "GardenFervorUnitTaskAgent.h"

#include "GardenFervorDeveloperSettings.h"
#include "GardenFervorLandscapeTerraformSubsystem.h"
#include "GardenFervorPhysicalEconomySubsystem.h"
#include "GardenFervorPhysicalResourceTypes.h"
#include "GardenFervorProjectSubsystem.h"
#include "GardenFervorTaskSubsystem.h"
#include "GardenFervorTerraformTypes.h"
#include "GardenFervorUnitBase.h"
#include "GardenFervorUnitCapabilityTypes.h"
#include "GardenFervorUnitDefinition.h"

DEFINE_LOG_CATEGORY_STATIC(LogGardenFervorAgent, Log, All);

namespace GardenFervorUnitTaskAgentPrivate
{
	/** C1/T9: prefer Task.OperationalResourceKey; legacy LevelPad leaves it unset → SpoilDirt. */
	FName ResolveOperationalResourceKey(const FGardenFervorTaskRecord& Task)
	{
		if (!Task.OperationalResourceKey.IsNone())
		{
			return Task.OperationalResourceKey;
		}
		return GardenFervorPhysicalResourceKey(EGardenFervorPhysicalResource::SpoilDirt);
	}
}

UGardenFervorUnitTaskAgent::UGardenFervorUnitTaskAgent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UGardenFervorUnitTaskAgent::BeginPlay()
{
	Super::BeginPlay();
	EnterState(EGardenFervorUnitAgentState::SeekTask);
}

void UGardenFervorUnitTaskAgent::TickComponent(
	float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bAutonomyEnabled)
	{
		ProcessAutonomy(DeltaTime);
	}
}

void UGardenFervorUnitTaskAgent::SetAutonomyEnabled(bool bEnabled)
{
	bAutonomyEnabled = bEnabled;
	if (!bEnabled && AssignedTaskId.IsValid())
	{
		AbortCurrentTask(TEXT("Autonomy disabled"));
	}
	if (bEnabled && AgentState == EGardenFervorUnitAgentState::Idle)
	{
		EnterState(EGardenFervorUnitAgentState::SeekTask);
	}
}

void UGardenFervorUnitTaskAgent::SetInstantMode(bool bEnabled)
{
	bInstantMode = bEnabled;
	if (bEnabled)
	{
		ExecuteDurationSeconds = 0.08f;
		PrepareDurationSeconds = 0.02f;
		WorkArrivalDistance = 5000.f;
		SeekRetrySeconds = 0.02f;
	}
}

void UGardenFervorUnitTaskAgent::SetProjectFilter(FGardenFervorProjectId ProjectId)
{
	ProjectFilter = ProjectId;
}

AGardenFervorUnitBase* UGardenFervorUnitTaskAgent::GetUnit() const
{
	return Cast<AGardenFervorUnitBase>(GetOwner());
}

UGardenFervorTaskSubsystem* UGardenFervorUnitTaskAgent::GetTasks() const
{
	const UWorld* World = GetWorld();
	return World ? World->GetSubsystem<UGardenFervorTaskSubsystem>() : nullptr;
}

UGardenFervorProjectSubsystem* UGardenFervorUnitTaskAgent::GetProjects() const
{
	const UWorld* World = GetWorld();
	return World ? World->GetSubsystem<UGardenFervorProjectSubsystem>() : nullptr;
}

UGardenFervorPhysicalEconomySubsystem* UGardenFervorUnitTaskAgent::GetEco() const
{
	const UWorld* World = GetWorld();
	return World ? World->GetSubsystem<UGardenFervorPhysicalEconomySubsystem>() : nullptr;
}

int32 UGardenFervorUnitTaskAgent::GetUnitInstanceId() const
{
	const AActor* Owner = GetOwner();
	return Owner ? static_cast<int32>(Owner->GetUniqueID()) : 0;
}

TArray<FName> UGardenFervorUnitTaskAgent::ResolveCapabilities() const
{
	TArray<FName> Caps;
	const AGardenFervorUnitBase* Unit = GetUnit();
	if (!Unit)
	{
		return Caps;
	}
	if (const UGardenFervorUnitDefinition* Def = Unit->GetDefinition())
	{
		if (Def->Capabilities.Num() > 0)
		{
			return Def->Capabilities;
		}
	}
	if (Unit->IsTerraformer())
	{
		Caps.Add(FName(TEXT("Terraform")));
	}
	else if (Unit->IsWorker())
	{
		Caps.Add(FName(TEXT("Worker")));
	}
	return Caps;
}

FVector UGardenFervorUnitTaskAgent::GetStockWorldLocation(int32 StockId) const
{
	if (StockId <= 0)
	{
		return FVector::ZeroVector;
	}
	if (UGardenFervorPhysicalEconomySubsystem* Eco = GetEco())
	{
		FGardenFervorPhysicalStockId Id;
		Id.Value = StockId;
		return Eco->GetStockLocation(Id);
	}
	return FVector::ZeroVector;
}

FVector UGardenFervorUnitTaskAgent::GetTaskWorkLocation(const FGardenFervorTaskRecord& Task) const
{
	if (Task.TaskType == EGardenFervorTaskType::Transport && Task.SourceStockId > 0)
	{
		return GetStockWorldLocation(Task.SourceStockId);
	}
	if (Task.TaskType == EGardenFervorTaskType::Extract && Task.SourceStockId > 0)
	{
		return GetStockWorldLocation(Task.SourceStockId);
	}
	if (Task.AreaBounds.IsValid)
	{
		return Task.AreaBounds.GetCenter();
	}
	const AGardenFervorUnitBase* Unit = GetUnit();
	return Unit ? Unit->GetActorLocation() : FVector::ZeroVector;
}

FVector UGardenFervorUnitTaskAgent::GetTaskDeliverLocation(const FGardenFervorTaskRecord& Task) const
{
	if (Task.DestStockId > 0)
	{
		return GetStockWorldLocation(Task.DestStockId);
	}
	return GetTaskWorkLocation(Task);
}

FString UGardenFervorUnitTaskAgent::GetAgentStatusText() const
{
	const TCHAR* Phase = TEXT("Idle");
	switch (AgentState)
	{
	case EGardenFervorUnitAgentState::SeekTask: Phase = TEXT("Seek"); break;
	case EGardenFervorUnitAgentState::Reserve: Phase = TEXT("Reserve"); break;
	case EGardenFervorUnitAgentState::Travel: Phase = TEXT("Travel"); break;
	case EGardenFervorUnitAgentState::Prepare: Phase = TEXT("Prepare"); break;
	case EGardenFervorUnitAgentState::Execute: Phase = TEXT("Execute"); break;
	case EGardenFervorUnitAgentState::Verify: Phase = TEXT("Verify"); break;
	case EGardenFervorUnitAgentState::Deliver: Phase = TEXT("Haul"); break;
	case EGardenFervorUnitAgentState::Report: Phase = TEXT("Report"); break;
	case EGardenFervorUnitAgentState::Replan: Phase = TEXT("Replan"); break;
	default: break;
	}
	if (CarriedAmount > 0.f)
	{
		return FString::Printf(TEXT("%s+%.0f"), Phase, CarriedAmount);
	}
	return FString(Phase);
}

void UGardenFervorUnitTaskAgent::EnterState(EGardenFervorUnitAgentState NewState)
{
	AgentState = NewState;
	StateTimer = 0.f;
	if (NewState == EGardenFervorUnitAgentState::Execute)
	{
		ExecuteElapsed = 0.f;
	}
}

void UGardenFervorUnitTaskAgent::AbortCurrentTask(const FString& Reason)
{
	LastReport = Reason;
	if (CarriedAmount > 0.f && !CarriedResource.IsNone())
	{
		if (UGardenFervorTaskSubsystem* Tasks = GetTasks())
		{
			FGardenFervorTaskRecord Task;
			if (AssignedTaskId.IsValid() && Tasks->GetTask(AssignedTaskId, Task) && Task.SourceStockId > 0)
			{
				if (UGardenFervorPhysicalEconomySubsystem* Eco = GetEco())
				{
					FGardenFervorPhysicalStockId Src;
					Src.Value = Task.SourceStockId;
					Eco->Deposit(Src, CarriedResource, CarriedAmount);
				}
			}
		}
		CarriedAmount = 0.f;
		CarriedResource = NAME_None;
	}
	if (UGardenFervorTaskSubsystem* Tasks = GetTasks())
	{
		if (AssignedTaskId.IsValid())
		{
			Tasks->ReleaseClaim(AssignedTaskId, GetUnitInstanceId());
		}
	}
	AssignedTaskId = FGardenFervorTaskId{};
	TravelTarget = FVector::ZeroVector;
	if (AGardenFervorUnitBase* Unit = GetUnit())
	{
		Unit->StopMoving();
	}
	EnterState(EGardenFervorUnitAgentState::Replan);
}

void UGardenFervorUnitTaskAgent::SyncProjectIfNeeded()
{
	UGardenFervorProjectSubsystem* Projects = GetProjects();
	UGardenFervorTaskSubsystem* Tasks = GetTasks();
	if (!Projects || !Tasks || !AssignedTaskId.IsValid())
	{
		return;
	}
	FGardenFervorTaskRecord Task;
	if (Tasks->GetTask(AssignedTaskId, Task) && Task.ProjectId.IsValid())
	{
		Projects->SyncProjectStatusFromTasks(Task.ProjectId);
	}
}

bool UGardenFervorUnitTaskAgent::ApplyMaterialEffectsForTask(const FGardenFervorTaskRecord& Task)
{
	UGardenFervorPhysicalEconomySubsystem* Eco = GetEco();
	UGardenFervorProjectSubsystem* Projects = GetProjects();
	if (!Projects)
	{
		return Task.TaskType != EGardenFervorTaskType::Terraform
			&& Task.TaskType != EGardenFervorTaskType::Extract
			&& Task.DisplayName != FName(TEXT("TransformFill"));
	}

	FGardenFervorProjectRecord Project;
	if (!Projects->GetProject(Task.ProjectId, Project))
	{
		return false;
	}

	const float Batch = MaterialBatchAmount;

	if (Task.TaskType == EGardenFervorTaskType::Extract)
	{
		if (!Eco)
		{
			return false;
		}
		const int32 PitId = Task.SourceStockId > 0 ? Task.SourceStockId : Project.LinkedPitStockId;
		if (PitId <= 0)
		{
			return false;
		}
		FGardenFervorPhysicalStockId StockId;
		StockId.Value = PitId;
		const FName ResourceKey = GardenFervorUnitTaskAgentPrivate::ResolveOperationalResourceKey(Task);
		return Eco->Deposit(StockId, ResourceKey, Batch);
	}
	if (Task.DisplayName == FName(TEXT("TransformFill")))
	{
		if (!Eco || Project.LinkedStockId <= 0)
		{
			return false;
		}
		FGardenFervorPhysicalStockId StockId;
		StockId.Value = Project.LinkedStockId;
		return Eco->TryTransform(
			StockId, FName(TEXT("SpoilDirt")), FName(TEXT("FillDirt")), Batch, 1.f);
	}
	if (Task.TaskType == EGardenFervorTaskType::Terraform)
	{
		UWorld* World = GetWorld();
		UGardenFervorLandscapeTerraformSubsystem* Terraform = World
			? World->GetSubsystem<UGardenFervorLandscapeTerraformSubsystem>()
			: nullptr;
		if (!Terraform)
		{
			return false;
		}

		const UGardenFervorDeveloperSettings* Settings = UGardenFervorDeveloperSettings::Get();
		const float Radius = Settings ? Settings->TerraformBrushRadius : 350.f;
		const float HeightDelta = Settings ? Settings->TerraformHeightDeltaCm : 40.f;
		const FVector WorkLoc = GetTaskWorkLocation(Task);

		EGardenFervorTerraformMode Mode = EGardenFervorTerraformMode::Raise;
		float Delta = HeightDelta;
		if (Task.DisplayName == FName(TEXT("LowerGrade")))
		{
			Mode = EGardenFervorTerraformMode::Lower;
		}
		else if (Task.DisplayName == FName(TEXT("CompactSite")))
		{
			Mode = EGardenFervorTerraformMode::Lower;
			Delta = HeightDelta * 0.25f;
		}

		bool bAny = false;
		for (int32 Pulse = 0; Pulse < 3; ++Pulse)
		{
			bAny |= Terraform->ApplyBrushAt(WorkLoc, Mode, Radius, Delta, 0.f, 0);
		}
		return bAny;
	}
	return true;
}

bool UGardenFervorUnitTaskAgent::LoadHaulFromSource(const FGardenFervorTaskRecord& Task)
{
	UGardenFervorPhysicalEconomySubsystem* Eco = GetEco();
	if (!Eco || Task.SourceStockId <= 0)
	{
		return false;
	}
	FGardenFervorPhysicalStockId Src;
	Src.Value = Task.SourceStockId;
	const FName Key = GardenFervorUnitTaskAgentPrivate::ResolveOperationalResourceKey(Task);
	const float Batch = MaterialBatchAmount;
	if (!Eco->Withdraw(Src, Key, Batch))
	{
		return false;
	}
	CarriedResource = Key;
	CarriedAmount = Batch;
	return true;
}

bool UGardenFervorUnitTaskAgent::UnloadHaulAtDest(const FGardenFervorTaskRecord& Task)
{
	UGardenFervorPhysicalEconomySubsystem* Eco = GetEco();
	if (!Eco || Task.DestStockId <= 0 || CarriedAmount <= 0.f || CarriedResource.IsNone())
	{
		return false;
	}
	FGardenFervorPhysicalStockId Dst;
	Dst.Value = Task.DestStockId;
	if (!Eco->Deposit(Dst, CarriedResource, CarriedAmount))
	{
		return false;
	}
	CarriedAmount = 0.f;
	CarriedResource = NAME_None;
	return true;
}

bool UGardenFervorUnitTaskAgent::TravelToward(AGardenFervorUnitBase* Unit, const FVector& Target)
{
	if (!Unit)
	{
		return false;
	}
	if (bInstantMode)
	{
		Unit->StopMoving();
		Unit->SnapToGroundAt(Target);
		return true;
	}
	const float Dist2D = FVector::Dist2D(Unit->GetActorLocation(), Target);
	if (Dist2D <= WorkArrivalDistance)
	{
		Unit->StopMoving();
		return true;
	}
	if (!Unit->IsMoving() || FVector::Dist2D(Unit->GetMoveTarget(), Target) > WorkArrivalDistance * 0.5f)
	{
		Unit->MoveToLocation(Target);
	}
	return false;
}

void UGardenFervorUnitTaskAgent::ProcessAutonomy(float DeltaSeconds)
{
	AGardenFervorUnitBase* Unit = GetUnit();
	UGardenFervorTaskSubsystem* Tasks = GetTasks();
	if (!Unit || !Tasks || DeltaSeconds < 0.f)
	{
		return;
	}

	StateTimer += DeltaSeconds;
	SeekCooldown = FMath::Max(0.f, SeekCooldown - DeltaSeconds);

	switch (AgentState)
	{
	case EGardenFervorUnitAgentState::Idle:
		EnterState(EGardenFervorUnitAgentState::SeekTask);
		break;

	case EGardenFervorUnitAgentState::SeekTask:
	{
		if (SeekCooldown > 0.f)
		{
			break;
		}
		FGardenFervorTaskRecord Candidate;
		if (!Tasks->FindBestReadyTaskForCapabilities(ResolveCapabilities(), Candidate, ProjectFilter))
		{
			SeekCooldown = SeekRetrySeconds;
			break;
		}
		AssignedTaskId = Candidate.TaskId;
		EnterState(EGardenFervorUnitAgentState::Reserve);
		break;
	}

	case EGardenFervorUnitAgentState::Reserve:
	{
		if (!Tasks->TryClaimTask(AssignedTaskId, GetUnitInstanceId()))
		{
			LastReport = Tasks->GetPrimaryFailureReason(AssignedTaskId);
			if (LastReport.IsEmpty())
			{
				LastReport = TEXT("Claim failed");
			}
			AssignedTaskId = FGardenFervorTaskId{};
			EnterState(EGardenFervorUnitAgentState::Report);
			break;
		}
		FGardenFervorTaskRecord Task;
		Tasks->GetTask(AssignedTaskId, Task);
		TravelTarget = GetTaskWorkLocation(Task);
		EnterState(EGardenFervorUnitAgentState::Travel);
		break;
	}

	case EGardenFervorUnitAgentState::Travel:
	{
		if (TravelToward(Unit, TravelTarget))
		{
			EnterState(EGardenFervorUnitAgentState::Prepare);
		}
		break;
	}

	case EGardenFervorUnitAgentState::Prepare:
	{
		const float Need = bInstantMode ? 0.f : PrepareDurationSeconds;
		if (StateTimer >= Need)
		{
			EnterState(EGardenFervorUnitAgentState::Execute);
		}
		break;
	}

	case EGardenFervorUnitAgentState::Execute:
	{
		FGardenFervorTaskRecord Task;
		if (!Tasks->GetTask(AssignedTaskId, Task))
		{
			AbortCurrentTask(TEXT("Execute missing task"));
			break;
		}

		if (Task.TaskType == EGardenFervorTaskType::Transport)
		{
			if (!LoadHaulFromSource(Task))
			{
				AbortCurrentTask(TEXT("Haul load failed (pit empty?)"));
				break;
			}
			TravelTarget = GetTaskDeliverLocation(Task);
			EnterState(EGardenFervorUnitAgentState::Deliver);
			break;
		}

		ExecuteElapsed += DeltaSeconds;
		const float Duration = FMath::Max(0.01f, ExecuteDurationSeconds);
		const float Progress = bInstantMode ? 1.f : FMath::Clamp(ExecuteElapsed / Duration, 0.f, 1.f);
		Tasks->SetTaskProgress(AssignedTaskId, Progress);
		if (Progress >= 1.f)
		{
			EnterState(EGardenFervorUnitAgentState::Verify);
		}
		break;
	}

	case EGardenFervorUnitAgentState::Deliver:
	{
		FGardenFervorTaskRecord Task;
		if (!Tasks->GetTask(AssignedTaskId, Task))
		{
			AbortCurrentTask(TEXT("Deliver missing task"));
			break;
		}

		if (Task.TaskType == EGardenFervorTaskType::Transport)
		{
			if (!TravelToward(Unit, TravelTarget))
			{
				break;
			}
			if (!UnloadHaulAtDest(Task))
			{
				AbortCurrentTask(TEXT("Haul unload failed"));
				break;
			}
			EnterState(EGardenFervorUnitAgentState::Verify);
			break;
		}

		// Non-transport: Deliver is a no-op hop back to seek.
		EnterState(EGardenFervorUnitAgentState::SeekTask);
		break;
	}

	case EGardenFervorUnitAgentState::Verify:
	{
		FGardenFervorTaskRecord Task;
		if (!Tasks->GetTask(AssignedTaskId, Task))
		{
			AbortCurrentTask(TEXT("Verify missing task"));
			break;
		}
		if (Task.TaskType != EGardenFervorTaskType::Transport)
		{
			if (!ApplyMaterialEffectsForTask(Task))
			{
				AbortCurrentTask(TEXT("Material effect failed (stock/transform)"));
				break;
			}
		}
		if (!Tasks->CompleteTask(AssignedTaskId))
		{
			AbortCurrentTask(TEXT("Verify/Complete failed"));
			break;
		}
		// T9 / C5: U3 Construction Build establishes Achevé (not TransformFill / Worker Build).
		if (Task.TaskType == EGardenFervorTaskType::Build
			&& Task.RequiredCapabilities.Contains(
				GardenFervorUnitCapabilityKey(EGardenFervorUnitCapability::Construction)))
		{
			if (UGardenFervorProjectSubsystem* Projects = GetProjects())
			{
				Projects->MarkConstructionComplete(Task.ProjectId);
			}
		}
		SyncProjectIfNeeded();
		AssignedTaskId = FGardenFervorTaskId{};
		EnterState(EGardenFervorUnitAgentState::Deliver);
		break;
	}

	case EGardenFervorUnitAgentState::Report:
		UE_LOG(LogGardenFervorAgent, Verbose, TEXT("%s agent report: %s"),
			*GetNameSafe(Unit), *LastReport);
		EnterState(EGardenFervorUnitAgentState::Replan);
		break;

	case EGardenFervorUnitAgentState::Replan:
		SeekCooldown = SeekRetrySeconds;
		EnterState(EGardenFervorUnitAgentState::SeekTask);
		break;
	}
}
