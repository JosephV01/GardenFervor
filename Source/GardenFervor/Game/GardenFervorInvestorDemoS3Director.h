// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GardenFervorProjectTypes.h"
#include "GardenFervorUnitCapabilityTypes.h"
#include "GardenFervorInvestorDemoS3Director.generated.h"

class AGardenFervorUnitBase;
class ATextRenderActor;
class UStaticMeshComponent;

/**
 * Investor Demo étape 3 — présentation asynchrone (Tick).
 * Orchestrates real T1→T9 APIs across frames so movement / PH feedback are visible.
 */
UCLASS()
class GARDENFERVOR_API AGardenFervorInvestorDemoS3Director : public AActor
{
	GENERATED_BODY()

public:
	AGardenFervorInvestorDemoS3Director();

	virtual void Tick(float DeltaSeconds) override;

	/** Start (or restart) the demo presentation. */
	void StartPresentation();

	bool IsRunning() const { return bRunning; }
	bool HasSucceeded() const { return bSucceeded; }

protected:
	enum class EPhase : uint8
	{
		Idle,
		BootLayout,
		CreateProject,
		ExpandActivate,
		SpawnUnits,
		AutonomousRun,
		Finish,
		Done
	};

	void Advance(float DeltaSeconds);
	void EnterPhase(EPhase NewPhase);
	bool ResolvePresentationActors();
	/** Only presentation actors we intentionally transform (PH_ / LBL_) — not whole-map Static meshes. */
	void EnsurePresentationMovable(AActor* Actor) const;
	void SnapActorToLandscape(AActor* Actor, const FVector& DesiredXY, float HoverZ) const;
	void PlaceChainOnLandscape();
	void AlignStocksToPhysicalEconomy();
	void SetLabelText(const TCHAR* Key, const FString& Text);
	void FaceLabelsToCamera();
	void SetPlaceholderActive(const TCHAR* Key, bool bActive, const FLinearColor& Accent);
	void ApplyUnitDemoColor(AGardenFervorUnitBase* Unit, const FLinearColor& Color) const;
	AGardenFervorUnitBase* SpawnDemoUnit(EGardenFervorCohortUnitRole CohortRole, const FVector& Location, const FLinearColor& Color);
	AActor* FindByKey(const TCHAR* Key) const;
	ATextRenderActor* FindLabel(const TCHAR* Key) const;
	bool SampleLandscape(const FVector& ApproxXY, FVector& OutLocation) const;

	EPhase Phase = EPhase::Idle;
	float PhaseTimer = 0.f;
	bool bRunning = false;
	bool bSucceeded = false;
	float PeakStockA = 0.f;

	FGardenFervorProjectId ProjectId;
	FVector WorkSiteCenter = FVector::ZeroVector;

	UPROPERTY()
	TObjectPtr<AGardenFervorUnitBase> UnitU1;
	UPROPERTY()
	TObjectPtr<AGardenFervorUnitBase> UnitU2;
	UPROPERTY()
	TObjectPtr<AGardenFervorUnitBase> UnitU3;

	UPROPERTY()
	TMap<FName, TObjectPtr<AActor>> PlaceholderByKey;
	UPROPERTY()
	TMap<FName, TObjectPtr<ATextRenderActor>> LabelByKey;
	UPROPERTY()
	TMap<FName, FVector> PlaceholderBaseScale;
};
