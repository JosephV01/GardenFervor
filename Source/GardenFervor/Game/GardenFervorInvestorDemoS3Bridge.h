// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GardenFervorProjectTypes.h"

class UWorld;

/**
 * Investor Demo étape 3 — entry point.
 * Starts async presentation director (real T1→T9 APIs + visible feedback).
 */
struct FGardenFervorInvestorDemoS3Bridge
{
	/**
	 * Starts the async S3 Cas A demo. Returns true if the director was started.
	 * Final ok=1 is logged by the director when the live path completes.
	 */
	static bool RunS3CasA(UWorld* World, FString& OutMessage);

	/** Optional: refresh labels if a project id is already known (no-op if director owns presentation). */
	static void RefreshPlaceholderLabels(UWorld* World, FGardenFervorProjectId ProjectId);
};
