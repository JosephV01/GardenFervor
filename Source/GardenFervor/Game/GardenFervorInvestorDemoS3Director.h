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
class UGardenFervorInvestorDemoPresentationWidget;

/**
 * Investor Demo — présentation asynchrone (Tick).
 * Orchestrates real T1→T9 APIs across frames so movement / PH feedback are visible.
 * Étape 4–5: caméra guidée + beats narratifs + UI légère (sans simuler le gameplay).
 */
UCLASS()
class GARDENFERVOR_API AGardenFervorInvestorDemoS3Director : public AActor
{
	GENERATED_BODY()

public:
	AGardenFervorInvestorDemoS3Director();

	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

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

	/** Investor-facing beats — derived from real systems, never invent events. */
	enum class EPresentationBeat : uint8
	{
		Idle = 0,
		Intention,
		Project,
		Analyse,
		WorkSite,
		Extraction,
		Transport,
		StockB,
		Construction,
		Acheve,
		EnService,
		Conclusion
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

	void SetPresentationBeat(EPresentationBeat NewBeat, const FString& Detail);
	void SetCameraFocus(const FVector& WorldXY, float ArmLength);
	void UpdateCamera(float DeltaSeconds);
	void EnsurePresentationWidget();
	void RefreshPresentationWidget();
	void TearDownPresentationWidget();
	void HighlightAutonomousUnit(AGardenFervorUnitBase* ActiveUnit);
	static void GetBeatMeta(EPresentationBeat Beat, int32& OutStep, FString& OutTitle);

	EPhase Phase = EPhase::Idle;
	float PhaseTimer = 0.f;
	bool bRunning = false;
	bool bSucceeded = false;
	float PeakStockA = 0.f;

	bool bCreateProjectApiDone = false;
	bool bExpandApiDone = false;
	bool bFinishLogged = false;
	bool bDriveCamera = false;

	EPresentationBeat PresentationBeat = EPresentationBeat::Idle;
	FString PresentationDetail;
	FVector CameraFocusXY = FVector::ZeroVector;
	float CameraArmLength = 3200.f;

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

	UPROPERTY()
	TObjectPtr<UGardenFervorInvestorDemoPresentationWidget> PresentationWidget;
};
