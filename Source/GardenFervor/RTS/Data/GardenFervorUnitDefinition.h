// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GardenFervorRTSTypes.h"
#include "GardenFervorUnitCapabilityTypes.h"
#include "GardenFervorUnitDefinition.generated.h"

class AGardenFervorUnitBase;
class UStaticMesh;
class UMaterialInterface;

UCLASS(BlueprintType)
class GARDENFERVOR_API UGardenFervorUnitDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|Unit")
	FName UnitId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|Unit")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|Unit")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|Unit")
	EGardenFervorTechAge RequiredAge = EGardenFervorTechAge::Age1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|Unit")
	TArray<FGardenFervorResourceAmount> TrainCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|Unit", meta = (ClampMin = "0.1"))
	float TrainTimeSeconds = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|Unit", meta = (ClampMin = "0"))
	int32 PopulationCost = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|Unit")
	bool bIsWorker = true;

	/**
	 * ODC-F5 / C2: capabilities advertised to the task graph (RequiredCapabilities match).
	 * Cohort S3: set via GardenFervorUnitCapabilityKey(Extraction|Transport|Construction)
	 * or GardenFervorCohortUnitCapabilities(U1|U2|U3). Opaque FName — no per-resource branches.
	 * Legacy LevelPad may still use Worker / Terraform. Empty = runtime fallback from UnitId / bIsWorker.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|Unit|Autonomy")
	TArray<FName> Capabilities;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|Unit")
	TSubclassOf<AGardenFervorUnitBase> UnitClass;

	/** Visual mesh (authored unit mesh or temporary placeholder). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|Unit|Visual")
	TSoftObjectPtr<UStaticMesh> PlaceholderMesh;

	/** Optional material override (e.g. T01 MI). Empty = keep mesh slot materials. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|Unit|Visual")
	TSoftObjectPtr<UMaterialInterface> DisplayMaterial;

	/** Relative scale applied to the mesh component. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|Unit|Visual")
	FVector MeshRelativeScale = FVector(1.f, 1.f, 1.f);

	/**
	 * Yaw offset (degrees) on the mesh so authored "forward" matches actor +X (move direction).
	 * T01 FBX faces -X → use 180.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|Unit|Visual")
	float MeshYawOffsetDegrees = 0.f;

	/**
	 * When true, skip BasicShape color tint MID (use DisplayMaterial / mesh materials).
	 * Selection uses ring + slight scale only.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS|Unit|Visual")
	bool bUseAuthoredAppearance = false;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(TEXT("GardenFervorUnit"), GetFName());
	}
};