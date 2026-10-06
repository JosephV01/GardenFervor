// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GardenFervorProjectTypes.h"

class UGardenFervorPhysicalEconomySubsystem;

/**
 * C5 / cohorte S3 — Complete ≠ En service.
 *
 * S3 criterion (not universal):
 *   bConstructionComplete && GetAvailable(Stock B, Timber) > 0  →  bInService
 *
 * Stock B = LinkedStockId (T4). Uses PE Timber key — never legacy Wood.
 * Does not consume Timber. Does not invent build costs.
 */

/** Available Timber on cohort Stock B (0 if missing / no eco). */
float GardenFervorGetCohortStockBTimberAvailable(
	const UGardenFervorPhysicalEconomySubsystem* Eco,
	const FGardenFervorProjectRecord& Project);

/** True when Stock B has Timber available above S3 threshold (> 0). */
bool GardenFervorCohortStockBHasTimber(
	const UGardenFervorPhysicalEconomySubsystem* Eco,
	const FGardenFervorProjectRecord& Project);

/**
 * Recompute Project.bInService from Complete + Stock B Timber.
 * Does not set bConstructionComplete. Does not Withdraw/Deposit.
 * @return current bInService after update.
 */
bool GardenFervorRefreshCohortServiceState(
	UGardenFervorPhysicalEconomySubsystem* Eco,
	FGardenFervorProjectRecord& Project);
