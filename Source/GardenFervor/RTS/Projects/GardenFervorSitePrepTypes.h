// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GardenFervorSitePrepTypes.generated.h"

/**
 * C3 / cohorte S3 — generic site preparation / extension parameters.
 * Driven by Project data, not by a LevelPad- or Forest-specific expander.
 * Cas A (S3 first proof): AlreadyReady → no Raise/Lower/Paint.
 */
UENUM(BlueprintType)
enum class EGardenFervorSitePrepMode : uint8
{
	None UMETA(DisplayName = "None"),
	/** Site already suitable — no terrain modification (S3 Cas A). */
	AlreadyReady UMETA(DisplayName = "Already Ready"),
	/** Future Cas B — terraform may be required; not executed by T5. */
	RequiresTerraform UMETA(DisplayName = "Requires Terraform"),
};

USTRUCT(BlueprintType)
struct FGardenFervorSitePrepParams
{
	GENERATED_BODY()

	/** How readiness is obtained for this work site. Cohort S3 default = AlreadyReady. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|SitePrep")
	EGardenFervorSitePrepMode Mode = EGardenFervorSitePrepMode::AlreadyReady;

	/**
	 * When true, terrain ops may be scheduled (Cas B).
	 * Must remain false for S3 Cas A — ApplySitePreparation will not modify terrain.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|SitePrep")
	bool bRequestTerrainModify = false;

	/** Optional future grade target (cm). Ignored when AlreadyReady / no terrain request. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|SitePrep")
	float TargetHeightOffsetCm = 0.f;
};

USTRUCT(BlueprintType)
struct FGardenFervorSitePrepResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "RTS|SitePrep")
	bool bSiteReady = false;

	/** Always false for T5 Cas A path. */
	UPROPERTY(BlueprintReadOnly, Category = "RTS|SitePrep")
	bool bTerrainOpsScheduled = false;

	UPROPERTY(BlueprintReadOnly, Category = "RTS|SitePrep")
	FString Detail;
};
