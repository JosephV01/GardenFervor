// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GardenFervorSitePrepTypes.h"
#include "GardenFervorProjectTypes.generated.h"

UENUM(BlueprintType)
enum class EGardenFervorProjectStatus : uint8
{
	Draft UMETA(DisplayName = "Draft"),
	Ready UMETA(DisplayName = "Ready"),
	Running UMETA(DisplayName = "Running"),
	Blocked UMETA(DisplayName = "Blocked"),
	Completed UMETA(DisplayName = "Completed"),
	Failed UMETA(DisplayName = "Failed"),
	Cancelled UMETA(DisplayName = "Cancelled"),
};

/** High-level objective kinds for F4 (ecology detail comes later). */
UENUM(BlueprintType)
enum class EGardenFervorProjectObjective : uint8
{
	None UMETA(DisplayName = "None"),
	/** Legacy ODC-F6/F7 consumer — Spoil/Fill/Raise pad. Not the generic work-site model. */
	LevelPad UMETA(DisplayName = "Level Pad"),
	SurveyOnly UMETA(DisplayName = "Survey Only"),
	/**
	 * C3 generic work site (cohorte S3). Parametrized by SitePrep + ZoneBounds + stocks A/B.
	 * Not ExpandForest. Not a LevelPad copy.
	 */
	WorkSite UMETA(DisplayName = "Work Site"),
};

USTRUCT(BlueprintType)
struct FGardenFervorProjectId
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Project")
	int32 Value = 0;

	bool IsValid() const { return Value > 0; }

	bool operator==(const FGardenFervorProjectId& Other) const { return Value == Other.Value; }
	friend uint32 GetTypeHash(const FGardenFervorProjectId& Id) { return GetTypeHash(Id.Value); }
};

USTRUCT(BlueprintType)
struct FGardenFervorProjectRecord
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Project")
	FGardenFervorProjectId ProjectId;

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Project")
	FName DisplayName = NAME_None;

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Project")
	EGardenFervorProjectObjective Objective = EGardenFervorProjectObjective::None;

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Project")
	EGardenFervorProjectStatus Status = EGardenFervorProjectStatus::Draft;

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Project")
	int32 Priority = 100;

	/** World-space AABB of the project footprint (cm). Site prep uses this zone. */
	UPROPERTY(BlueprintReadOnly, Category = "RTS|Project")
	FBox ZoneBounds = FBox(ForceInit);

	/**
	 * C3: generic site preparation / extension parameters for WorkSite (and future sites).
	 * Default AlreadyReady = S3 Cas A (no terraform).
	 */
	UPROPERTY(BlueprintReadOnly, Category = "RTS|Project|SitePrep")
	FGardenFervorSitePrepParams SitePrep;

	/** C3: set by GardenFervorApplySitePreparation. */
	UPROPERTY(BlueprintReadOnly, Category = "RTS|Project|SitePrep")
	bool bSitePrepResolved = false;

	/** C3: true when Cas A (or future successful prep) — site usable without pending terrain ops. */
	UPROPERTY(BlueprintReadOnly, Category = "RTS|Project|SitePrep")
	bool bSiteReady = false;

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Project")
	FString BlockReason;

	UPROPERTY(BlueprintReadOnly, Category = "RTS|Project")
	TArray<int32> TaskIds;

	/**
	 * ODC-F6/F7 pad / chantier stock (transform + consume).
	 * T4 / cohorte S3: also Stock B (destination) — Timber available after haul (Option A).
	 * Distinct PE StockId from LinkedPitStockId. Create via GardenFervorEnsureCohortStocks.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "RTS|Project")
	int32 LinkedStockId = 0;

	/**
	 * ODC-F7 extraction pit stock (spoil produced here, then hauled).
	 * T4 / cohorte S3: also Stock A (production / extract deposit) — PE identity mapping only.
	 * Semantic risk: name retains "Pit"; cohort WorkSite must not treat this as Spoil quarry gameplay.
	 * Distinct PE StockId from LinkedStockId. Create via GardenFervorEnsureCohortStocks.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "RTS|Project")
	int32 LinkedPitStockId = 0;
};
