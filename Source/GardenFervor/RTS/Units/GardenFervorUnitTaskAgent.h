// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GardenFervorTaskTypes.h"
#include "GardenFervorUnitTaskAgent.generated.h"

class AGardenFervorUnitBase;
class UGardenFervorTaskSubsystem;
class UGardenFervorProjectSubsystem;
class UGardenFervorPhysicalEconomySubsystem;

UENUM(BlueprintType)
enum class EGardenFervorUnitAgentState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	SeekTask UMETA(DisplayName = "Seek Task"),
	Reserve UMETA(DisplayName = "Reserve"),
	Travel UMETA(DisplayName = "Travel"),
	Prepare UMETA(DisplayName = "Prepare"),
	Execute UMETA(DisplayName = "Execute"),
	Verify UMETA(DisplayName = "Verify"),
	Deliver UMETA(DisplayName = "Deliver"),
	Report UMETA(DisplayName = "Report"),
	Replan UMETA(DisplayName = "Replan"),
};

/**
 * ODC-F5/F7 unit autonomy: SEEK → RESERVE → TRAVEL → PREPARE → EXECUTE → VERIFY → DELIVER.
 * Transport tasks load at SourceStock then deliver to DestStock (haul).
 */
UCLASS(ClassGroup = (GardenFervor), meta = (BlueprintSpawnableComponent))
class GARDENFERVOR_API UGardenFervorUnitTaskAgent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGardenFervorUnitTaskAgent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "RTS|Autonomy")
	void SetAutonomyEnabled(bool bEnabled);

	UFUNCTION(BlueprintPure, Category = "RTS|Autonomy")
	bool IsAutonomyEnabled() const { return bAutonomyEnabled; }

	UFUNCTION(BlueprintCallable, Category = "RTS|Autonomy")
	void SetInstantMode(bool bEnabled);

	UFUNCTION(BlueprintPure, Category = "RTS|Autonomy")
	bool IsInstantMode() const { return bInstantMode; }

	UFUNCTION(BlueprintCallable, Category = "RTS|Autonomy")
	void SetProjectFilter(FGardenFervorProjectId ProjectId);

	UFUNCTION(BlueprintPure, Category = "RTS|Autonomy")
	EGardenFervorUnitAgentState GetAgentState() const { return AgentState; }

	UFUNCTION(BlueprintPure, Category = "RTS|Autonomy")
	FGardenFervorTaskId GetAssignedTaskId() const { return AssignedTaskId; }

	UFUNCTION(BlueprintPure, Category = "RTS|Autonomy")
	FString GetAgentStatusText() const;

	UFUNCTION(BlueprintCallable, Category = "RTS|Autonomy")
	void ProcessAutonomy(float DeltaSeconds);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|Autonomy", meta = (ClampMin = "0.05"))
	float ExecuteDurationSeconds = 1.25f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|Autonomy", meta = (ClampMin = "0.0"))
	float PrepareDurationSeconds = 0.15f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|Autonomy", meta = (ClampMin = "50.0"))
	float WorkArrivalDistance = 180.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|Autonomy", meta = (ClampMin = "0.05"))
	float SeekRetrySeconds = 0.35f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|Autonomy", meta = (ClampMin = "1.0"))
	float MaterialBatchAmount = 10.f;

protected:
	AGardenFervorUnitBase* GetUnit() const;
	UGardenFervorTaskSubsystem* GetTasks() const;
	UGardenFervorProjectSubsystem* GetProjects() const;
	UGardenFervorPhysicalEconomySubsystem* GetEco() const;
	TArray<FName> ResolveCapabilities() const;
	int32 GetUnitInstanceId() const;
	FVector GetStockWorldLocation(int32 StockId) const;
	FVector GetTaskWorkLocation(const FGardenFervorTaskRecord& Task) const;
	FVector GetTaskDeliverLocation(const FGardenFervorTaskRecord& Task) const;
	void EnterState(EGardenFervorUnitAgentState NewState);
	void AbortCurrentTask(const FString& Reason);
	void SyncProjectIfNeeded();
	bool ApplyMaterialEffectsForTask(const FGardenFervorTaskRecord& Task);
	bool LoadHaulFromSource(const FGardenFervorTaskRecord& Task);
	bool UnloadHaulAtDest(const FGardenFervorTaskRecord& Task);
	bool TravelToward(AGardenFervorUnitBase* Unit, const FVector& Target);

	bool bAutonomyEnabled = true;
	bool bInstantMode = false;
	EGardenFervorUnitAgentState AgentState = EGardenFervorUnitAgentState::Idle;
	FGardenFervorTaskId AssignedTaskId;
	FGardenFervorProjectId ProjectFilter;
	FVector TravelTarget = FVector::ZeroVector;
	float StateTimer = 0.f;
	float SeekCooldown = 0.f;
	float ExecuteElapsed = 0.f;
	FString LastReport;

	FName CarriedResource = NAME_None;
	float CarriedAmount = 0.f;
};
