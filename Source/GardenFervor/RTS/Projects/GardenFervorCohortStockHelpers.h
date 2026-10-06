// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GardenFervorProjectTypes.h"

class UGardenFervorPhysicalEconomySubsystem;

/**
 * T4 / cohorte S3 — two distinct PhysicalEconomy stocks per Project.
 *
 * Mapping (no second stock architecture; reuses existing Project fields):
 *   Stock A (production / extract)  = Project.LinkedPitStockId
 *   Stock B (destination / available) = Project.LinkedStockId
 *
 * Future tasks: SourceStockId ← A · DestStockId ← B · OperationalResourceKey ← Timber (PE).
 * Does not perform transport or Deposit — structure only.
 */

/** Stock A id (0 = missing). */
inline int32 GardenFervorCohortStockAId(const FGardenFervorProjectRecord& Project)
{
	return Project.LinkedPitStockId;
}

/** Stock B id (0 = missing). */
inline int32 GardenFervorCohortStockBId(const FGardenFervorProjectRecord& Project)
{
	return Project.LinkedStockId;
}

inline bool GardenFervorCohortStocksAreDistinct(const FGardenFervorProjectRecord& Project)
{
	const int32 A = GardenFervorCohortStockAId(Project);
	const int32 B = GardenFervorCohortStockBId(Project);
	return A > 0 && B > 0 && A != B;
}

/**
 * Create Stock A and Stock B via PhysicalEconomy::CreateStock if missing.
 * Ensures A ≠ B. Idempotent when already distinct and valid.
 * @return true when Project holds two distinct stock ids.
 */
bool GardenFervorEnsureCohortStocks(
	UGardenFervorPhysicalEconomySubsystem* Eco,
	FGardenFervorProjectRecord& Project);
