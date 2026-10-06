// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GardenFervorPhysicalResourceTypes.generated.h"

/**
 * ODC-F6 / cohorte S3 physical materials (PhysicalEconomy ResourceKey).
 * Distinct from legacy AoE Food/Wood/Stone/Gold (EconomyComponent) — Wood is NOT a PE key.
 * Cohort wood key: Timber (C7 / Formalisation 03).
 */
UENUM(BlueprintType)
enum class EGardenFervorPhysicalResource : uint8
{
	None UMETA(DisplayName = "None"),
	SpoilDirt UMETA(DisplayName = "Spoil Dirt"),
	FillDirt UMETA(DisplayName = "Fill Dirt"),
	/** Official GardenFervor wood resource for PhysicalEconomy (cohort S3). Not legacy Wood. */
	Timber UMETA(DisplayName = "Timber"),
};

USTRUCT(BlueprintType)
struct FGardenFervorPhysicalStockId
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "RTS|PhysicalEconomy")
	int32 Value = 0;

	bool IsValid() const { return Value > 0; }
	bool operator==(const FGardenFervorPhysicalStockId& Other) const { return Value == Other.Value; }
	friend uint32 GetTypeHash(const FGardenFervorPhysicalStockId& Id) { return GetTypeHash(Id.Value); }
};

USTRUCT(BlueprintType)
struct FGardenFervorPhysicalStockRecord
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "RTS|PhysicalEconomy")
	FGardenFervorPhysicalStockId StockId;

	UPROPERTY(BlueprintReadOnly, Category = "RTS|PhysicalEconomy")
	FName DisplayName = NAME_None;

	UPROPERTY(BlueprintReadOnly, Category = "RTS|PhysicalEconomy")
	FVector Location = FVector::ZeroVector;

	/** Available amounts by resource key (SpoilDirt / FillDirt / Timber, …). */
	UPROPERTY(BlueprintReadOnly, Category = "RTS|PhysicalEconomy")
	TMap<FName, float> Amounts;

	/** Reserved amounts by resource key (held for tasks). */
	UPROPERTY(BlueprintReadOnly, Category = "RTS|PhysicalEconomy")
	TMap<FName, float> Reserved;

	float GetAvailable(FName ResourceKey) const
	{
		const float Have = Amounts.FindRef(ResourceKey);
		const float Held = Reserved.FindRef(ResourceKey);
		return FMath::Max(0.f, Have - Held);
	}
};

inline FName GardenFervorPhysicalResourceKey(EGardenFervorPhysicalResource Resource)
{
	switch (Resource)
	{
	case EGardenFervorPhysicalResource::SpoilDirt: return FName(TEXT("SpoilDirt"));
	case EGardenFervorPhysicalResource::FillDirt: return FName(TEXT("FillDirt"));
	case EGardenFervorPhysicalResource::Timber: return FName(TEXT("Timber"));
	default: return NAME_None;
	}
}
