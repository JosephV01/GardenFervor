// Copyright Epic Games, Inc. All Rights Reserved.

#include "GardenFervorCohortServiceHelpers.h"
#include "GardenFervorCohortObservabilityHelpers.h"

float GardenFervorGetCohortStockBTimberAvailable(
	const UGardenFervorPhysicalEconomySubsystem* Eco,
	const FGardenFervorProjectRecord& Project)
{
	// Same PE truth as C6 observability (no mirror).
	return GardenFervorGetCohortStockBTimberAvailableLive(Eco, Project);
}

bool GardenFervorCohortStockBHasTimber(
	const UGardenFervorPhysicalEconomySubsystem* Eco,
	const FGardenFervorProjectRecord& Project)
{
	return GardenFervorGetCohortStockBTimberAvailable(Eco, Project) > 0.f;
}

bool GardenFervorRefreshCohortServiceState(
	UGardenFervorPhysicalEconomySubsystem* Eco,
	FGardenFervorProjectRecord& Project)
{
	// S3-only rule: Complete ∧ Stock B Timber > 0. No consumption.
	const bool bShouldBeInService =
		Project.bConstructionComplete && GardenFervorCohortStockBHasTimber(Eco, Project);
	Project.bInService = bShouldBeInService;
	return Project.bInService;
}
