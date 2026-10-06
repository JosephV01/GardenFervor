// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GardenFervorProjectTypes.h"

class UGardenFervorPhysicalEconomySubsystem;

/**
 * C6 / cohorte S3 — PhysicalEconomy observability (read-only).
 * Values are always queried live from PE GetAvailable — no mirror counters.
 * Stock A = LinkedPitStockId · Stock B = LinkedStockId · key = PE Timber.
 */

float GardenFervorGetCohortStockATimberAvailable(
	const UGardenFervorPhysicalEconomySubsystem* Eco,
	const FGardenFervorProjectRecord& Project);

float GardenFervorGetCohortStockBTimberAvailableLive(
	const UGardenFervorPhysicalEconomySubsystem* Eco,
	const FGardenFervorProjectRecord& Project);

/**
 * Structured diagnostic line, e.g.:
 * C6 PE Project#N · StockA id=X Timber=a · StockB id=Y Timber=b · Complete=c EnService=s
 */
FString GardenFervorFormatCohortPhysicalEconomySnapshot(
	const UGardenFervorPhysicalEconomySubsystem* Eco,
	const FGardenFervorProjectRecord& Project);
