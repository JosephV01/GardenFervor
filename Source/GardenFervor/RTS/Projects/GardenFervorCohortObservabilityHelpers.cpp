// Copyright Epic Games, Inc. All Rights Reserved.

#include "GardenFervorCohortObservabilityHelpers.h"
#include "GardenFervorCohortStockHelpers.h"
#include "GardenFervorPhysicalEconomySubsystem.h"
#include "GardenFervorPhysicalResourceTypes.h"

namespace GardenFervorCohortObservabilityPrivate
{
	float GetTimberAtStock(
		const UGardenFervorPhysicalEconomySubsystem* Eco,
		const int32 StockIdValue)
	{
		if (!Eco || StockIdValue <= 0)
		{
			return 0.f;
		}
		FGardenFervorPhysicalStockId Id;
		Id.Value = StockIdValue;
		return Eco->GetAvailable(
			Id,
			GardenFervorPhysicalResourceKey(EGardenFervorPhysicalResource::Timber));
	}
}

float GardenFervorGetCohortStockATimberAvailable(
	const UGardenFervorPhysicalEconomySubsystem* Eco,
	const FGardenFervorProjectRecord& Project)
{
	return GardenFervorCohortObservabilityPrivate::GetTimberAtStock(
		Eco, GardenFervorCohortStockAId(Project));
}

float GardenFervorGetCohortStockBTimberAvailableLive(
	const UGardenFervorPhysicalEconomySubsystem* Eco,
	const FGardenFervorProjectRecord& Project)
{
	return GardenFervorCohortObservabilityPrivate::GetTimberAtStock(
		Eco, GardenFervorCohortStockBId(Project));
}

FString GardenFervorFormatCohortPhysicalEconomySnapshot(
	const UGardenFervorPhysicalEconomySubsystem* Eco,
	const FGardenFervorProjectRecord& Project)
{
	const int32 IdA = GardenFervorCohortStockAId(Project);
	const int32 IdB = GardenFervorCohortStockBId(Project);
	const float TimberA = GardenFervorGetCohortStockATimberAvailable(Eco, Project);
	const float TimberB = GardenFervorGetCohortStockBTimberAvailableLive(Eco, Project);

	return FString::Printf(
		TEXT("C6 PE Project#%d · StockA id=%d Timber=%.1f · StockB id=%d Timber=%.1f · Complete=%d EnService=%d"),
		Project.ProjectId.Value,
		IdA,
		TimberA,
		IdB,
		TimberB,
		Project.bConstructionComplete ? 1 : 0,
		Project.bInService ? 1 : 0);
}
