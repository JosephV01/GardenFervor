// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GardenFervorUnitCapabilityTypes.generated.h"

/**
 * C2 / cohorte S3 — official unit capability keys for task matching.
 * Carried on UGardenFervorUnitDefinition::Capabilities (FName), same channel as Task.RequiredCapabilities.
 * Not resource keys (Timber stays PhysicalEconomy). Not legacy Worker catch-all.
 */
UENUM(BlueprintType)
enum class EGardenFervorUnitCapability : uint8
{
	None UMETA(DisplayName = "None"),
	/** U1 — Extract tasks (resource chosen via Task.OperationalResourceKey). */
	Extraction UMETA(DisplayName = "Extraction"),
	/** U2 — Transport / haul between stocks. */
	Transport UMETA(DisplayName = "Transport"),
	/** U3 — Construction / build tasks. */
	Construction UMETA(DisplayName = "Construction"),
};

/**
 * Cohort S3 roster roles — specialized by capabilities on UnitDefinition, not by C++ subclasses.
 */
UENUM(BlueprintType)
enum class EGardenFervorCohortUnitRole : uint8
{
	None UMETA(DisplayName = "None"),
	U1 UMETA(DisplayName = "U1 Exploitation"),
	U2 UMETA(DisplayName = "U2 Transport"),
	U3 UMETA(DisplayName = "U3 Construction"),
};

inline FName GardenFervorUnitCapabilityKey(EGardenFervorUnitCapability Capability)
{
	switch (Capability)
	{
	case EGardenFervorUnitCapability::Extraction: return FName(TEXT("Extraction"));
	case EGardenFervorUnitCapability::Transport: return FName(TEXT("Transport"));
	case EGardenFervorUnitCapability::Construction: return FName(TEXT("Construction"));
	default: return NAME_None;
	}
}

inline FName GardenFervorCohortUnitId(EGardenFervorCohortUnitRole Role)
{
	switch (Role)
	{
	case EGardenFervorCohortUnitRole::U1: return FName(TEXT("U1"));
	case EGardenFervorCohortUnitRole::U2: return FName(TEXT("U2"));
	case EGardenFervorCohortUnitRole::U3: return FName(TEXT("U3"));
	default: return NAME_None;
	}
}

/** Capabilities that define a cohort role (single specialized cap — not Worker). */
inline TArray<FName> GardenFervorCohortUnitCapabilities(EGardenFervorCohortUnitRole Role)
{
	TArray<FName> Caps;
	switch (Role)
	{
	case EGardenFervorCohortUnitRole::U1:
		Caps.Add(GardenFervorUnitCapabilityKey(EGardenFervorUnitCapability::Extraction));
		break;
	case EGardenFervorCohortUnitRole::U2:
		Caps.Add(GardenFervorUnitCapabilityKey(EGardenFervorUnitCapability::Transport));
		break;
	case EGardenFervorCohortUnitRole::U3:
		Caps.Add(GardenFervorUnitCapabilityKey(EGardenFervorUnitCapability::Construction));
		break;
	default:
		break;
	}
	return Caps;
}
