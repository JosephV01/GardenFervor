// Copyright Epic Games, Inc. All Rights Reserved.

#include "GardenFervorCohortServiceHelpers.h"
#include "GardenFervorCohortStockHelpers.h"
#include "GardenFervorPhysicalEconomySubsystem.h"
#include "GardenFervorPhysicalResourceTypes.h"

float GardenFervorGetCohortStockBTimberAvailable(
	const UGardenFervorPhysicalEconomySubsystem* Eco,
	const FGardenFervorProjectRecord& Project)
{
	if (!Eco)
	{
		return 0.f;
	}
	const int32 StockB = GardenFervorCohortStockBId(Project);
	if (StockB <= 0)
	{
		return 0.f;
	}
	FGardenFervorPhysicalStockId Id;
	Id.Value = StockB;
	return Eco->GetAvailable(Id, GardenFervorPhysicalResourceKey(EGardenFervorPhysicalResource::Timber));
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
