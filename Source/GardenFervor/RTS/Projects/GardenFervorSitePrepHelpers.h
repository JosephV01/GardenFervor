// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GardenFervorProjectTypes.h"
#include "GardenFervorSitePrepTypes.h"

class UGardenFervorPhysicalEconomySubsystem;

/**
 * C3 — apply generic site preparation from Project.SitePrep (+ ZoneBounds).
 * Cas A (AlreadyReady / no terrain request): ensures cohort stocks A/B, marks site ready,
 * schedules no Terraform. Not ExpandForest. Not a LevelPad copy.
 *
 * LinkedPitStockId: used only as Stock A PE identity via GardenFervorEnsureCohortStocks —
 * no Pit/Quarry/Worker gameplay reactivation.
 */
bool GardenFervorApplySitePreparation(
	UGardenFervorPhysicalEconomySubsystem* Eco,
	FGardenFervorProjectRecord& Project,
	FGardenFervorSitePrepResult& OutResult);
