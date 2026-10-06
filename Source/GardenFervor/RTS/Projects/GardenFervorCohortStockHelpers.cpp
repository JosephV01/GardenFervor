// Copyright Epic Games, Inc. All Rights Reserved.

#include "GardenFervorCohortStockHelpers.h"
#include "GardenFervorPhysicalEconomySubsystem.h"

bool GardenFervorEnsureCohortStocks(
	UGardenFervorPhysicalEconomySubsystem* Eco,
	FGardenFervorProjectRecord& Project)
{
	if (!Eco)
	{
		return false;
	}

	const FVector Center = Project.ZoneBounds.IsValid
		? Project.ZoneBounds.GetCenter()
		: FVector::ZeroVector;
	// Offset so A and B are independent sites (haul will matter later; not performed here).
	const FVector LocA = Center + FVector(-1500.f, 0.f, 0.f);
	const FVector LocB = Center + FVector(1500.f, 0.f, 0.f);

	if (Project.LinkedPitStockId <= 0)
	{
		const FGardenFervorPhysicalStockId IdA = Eco->CreateStock(
			FName(*FString::Printf(TEXT("CohortStockA_%d"), Project.ProjectId.Value)),
			LocA);
		Project.LinkedPitStockId = IdA.Value;
	}

	if (Project.LinkedStockId <= 0 || Project.LinkedStockId == Project.LinkedPitStockId)
	{
		const FGardenFervorPhysicalStockId IdB = Eco->CreateStock(
			FName(*FString::Printf(TEXT("CohortStockB_%d"), Project.ProjectId.Value)),
			LocB);
		Project.LinkedStockId = IdB.Value;
	}

	return GardenFervorCohortStocksAreDistinct(Project);
}
