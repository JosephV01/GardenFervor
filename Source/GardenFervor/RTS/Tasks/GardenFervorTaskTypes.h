// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GardenFervorProjectTypes.h"
#include "GardenFervorTaskTypes.generated.h"

UENUM(BlueprintType)
enum class EGardenFervorTaskType : uint8
{
	Analyze UMETA(DisplayName = "Analyze"),
	Prepare UMETA(DisplayName = "Prepare"),
	Extract UMETA(DisplayName = "Extract"),
	Transport UMETA(DisplayName = "Transport"),
	Terraform UMETA(DisplayName = "Terraform"),
	Build UMETA(DisplayName = "Build"),
	Verify UMETA(DisplayName = "Verify"),
	Ecology UMETA(DisplayName = "Ecology"),
};

UENUM(BlueprintType)
enum class EGardenFervorTaskStatus : uint8
{
	Pending UMETA(DisplayName = "Pending"),
	Ready UMETA(DisplayName = "Ready"),
	Reserved UMETA(DisplayName = "Reserved"),
	Running UMETA(DisplayName = "Running"),
	Blocked UMETA(DisplayName = "Blocked"),
	Completed UMETA(DisplayName = "Completed"),
	Failed UMETA(DisplayName = "Failed"),
	Cancelled UMETA(DisplayName = "Cancelled"),
};

UENUM(BlueprintType)
enum class EGardenFervorTaskBlockCause : uint8
{
	None UMETA(DisplayName = "None"),
	WaitingPrerequisites UMETA(DisplayName = "Waiting Prerequisites"),
	MissingResource UMETA(DisplayName = "Missing Resource"),
	ReservationConflict UMETA(DisplayName = "Reservation Conflict"),
	MissingCapability UMETA(DisplayName = "Missing Capability"),
	AreaInaccessible UMETA(DisplayName = "Area Inaccessible"),
	ProjectCancelled UMETA(DisplayName = "Project Cancelled"),
	Unknown UMETA(DisplayName = "Unknown"),
};

USTRUCT(BlueprintType)
struct FGardenFervorTaskId
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	int32 Value = 0;

	bool IsValid() const { return Value > 0; }
	bool operator==(const FGardenFervorTaskId& Other) const { return Value == Other.Value; }
	friend uint32 GetTypeHash(const FGardenFervorTaskId& Id) { return GetTypeHash(Id.Value); }
};

USTRUCT(BlueprintType)
struct FGardenFervorResourceReservation
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	FName ResourceKey = NAME_None;

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	float Amount = 0.f;

	/** If true, only one task may hold this key at a time. */
	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	bool bExclusive = true;

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	bool bHeld = false;

	/** ODC-F6: physical stock site for this reservation (0 = legacy ResourcePool). */
	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	int32 StockId = 0;
};

USTRUCT(BlueprintType)
struct FGardenFervorTaskRecord
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	FGardenFervorTaskId TaskId;

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	FGardenFervorProjectId ProjectId;

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	EGardenFervorTaskType TaskType = EGardenFervorTaskType::Analyze;

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	FName DisplayName = NAME_None;

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	EGardenFervorTaskStatus Status = EGardenFervorTaskStatus::Pending;

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	TArray<int32> PrerequisiteTaskIds;

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	FBox AreaBounds = FBox(ForceInit);

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	TArray<FName> RequiredCapabilities;

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	int32 Priority = 100;

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	FGardenFervorResourceReservation Reservation;

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	float Progress = 0.f;

	/** Actor UniqueID of the unit that claimed this task (0 = unassigned). */
	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	int32 AssignedUnitInstanceId = 0;

	/** ODC-F7: haul from source stock (Transport tasks). */
	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	int32 SourceStockId = 0;

	/** ODC-F7: haul destination stock (Transport tasks). */
	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	int32 DestStockId = 0;

	/**
	 * C1 / cohorte S3: PhysicalEconomy resource this task manipulates (Extract / Transport / …).
	 * Set via GardenFervorPhysicalResourceKey(...) — e.g. Timber. Opaque FName; no per-resource branches.
	 * Distinct from Reservation.ResourceKey (consume/reserve), which may differ.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	FName OperationalResourceKey = NAME_None;

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	EGardenFervorTaskBlockCause BlockCause = EGardenFervorTaskBlockCause::None;

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Task")
	FString FailureReason;
};
