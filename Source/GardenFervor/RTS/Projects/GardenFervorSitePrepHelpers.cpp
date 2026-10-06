// Copyright Epic Games, Inc. All Rights Reserved.

#include "GardenFervorSitePrepHelpers.h"
#include "GardenFervorCohortStockHelpers.h"
#include "GardenFervorPhysicalEconomySubsystem.h"

bool GardenFervorApplySitePreparation(
	UGardenFervorPhysicalEconomySubsystem* Eco,
	FGardenFervorProjectRecord& Project,
	FGardenFervorSitePrepResult& OutResult)
{
	OutResult = FGardenFervorSitePrepResult{};

	if (!Eco)
	{
		OutResult.Detail = TEXT("PhysicalEconomy missing");
		return false;
	}

	if (!Project.ZoneBounds.IsValid)
	{
		OutResult.Detail = TEXT("Project.ZoneBounds invalid");
		return false;
	}

	// T4 stocks A/B — structure only (no Withdraw / Deposit / haul).
	if (!GardenFervorEnsureCohortStocks(Eco, Project))
	{
		OutResult.Detail = TEXT("Cohort stocks A/B could not be ensured");
		return false;
	}

	const FGardenFervorSitePrepParams& Params = Project.SitePrep;

	if (Params.Mode == EGardenFervorSitePrepMode::None)
	{
		OutResult.Detail = TEXT("SitePrep.Mode is None");
		return false;
	}

	// Cas A: already ready — never schedule Raise/Lower/Paint in T5.
	if (Params.Mode == EGardenFervorSitePrepMode::AlreadyReady || !Params.bRequestTerrainModify)
	{
		Project.bSitePrepResolved = true;
		Project.bSiteReady = true;
		OutResult.bSiteReady = true;
		OutResult.bTerrainOpsScheduled = false;
		OutResult.Detail = TEXT("Cas A: site already ready; no terraform scheduled");
		return true;
	}

	// RequiresTerraform + bRequestTerrainModify — Cas B not implemented in T5.
	Project.bSitePrepResolved = true;
	Project.bSiteReady = false;
	OutResult.bSiteReady = false;
	OutResult.bTerrainOpsScheduled = false;
	OutResult.Detail = TEXT("RequiresTerraform not executed in T5 (Cas A only)");
	return false;
}
