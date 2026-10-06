// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GardenFervorProjectTypes.h"
#include "GardenFervorProjectSubsystem.generated.h"

class UGardenFervorTaskSubsystem;

/**
 * ODC-F4 Projects: register projects and expand simple objectives into a task chain.
 */
UCLASS()
class GARDENFERVOR_API UGardenFervorProjectSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return true; }
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "RTS|Project")
	FGardenFervorProjectId CreateProject(
		FName DisplayName,
		EGardenFervorProjectObjective Objective,
		const FBox& ZoneBounds,
		int32 Priority = 100);

	/**
	 * C4 — Intention → Project (planning only).
	 * No EconomyComponent / TrySpend / BeginPlace / Ages / expand / units / terraform.
	 */
	UFUNCTION(BlueprintCallable, Category = "RTS|Project|Intention")
	FGardenFervorProjectId CreateProjectFromIntention(
		FName IntentionId,
		EGardenFervorProjectObjective Objective,
		const FBox& ZoneBounds,
		int32 Priority = 100);

	UFUNCTION(BlueprintPure, Category = "RTS|Project")
	bool GetProject(FGardenFervorProjectId ProjectId, FGardenFervorProjectRecord& OutProject) const;

	UFUNCTION(BlueprintPure, Category = "RTS|Project")
	TArray<FGardenFervorProjectRecord> GetAllProjects() const;

	/** Expand Draft/Ready project into tasks (simple planners). Returns task count. */
	UFUNCTION(BlueprintCallable, Category = "RTS|Project")
	int32 ExpandProjectToTasks(FGardenFervorProjectId ProjectId);

	UFUNCTION(BlueprintCallable, Category = "RTS|Project")
	bool ActivateProject(FGardenFervorProjectId ProjectId);

	UFUNCTION(BlueprintCallable, Category = "RTS|Project")
	void SyncProjectStatusFromTasks(FGardenFervorProjectId ProjectId);

	UFUNCTION(BlueprintCallable, Category = "RTS|Project")
	void ClearAll();

	UFUNCTION(BlueprintPure, Category = "RTS|Project")
	int32 GetProjectCount() const { return Projects.Num(); }

	/**
	 * Provisional F5 human smoke (UI / console): create + expand + activate a LevelPad
	 * near Center, seed FillDirt stub, optionally ensure a Worker + Terraformer exist.
	 * Returns invalid id on failure; OutMessage always filled for HUD/log.
	 */
	UFUNCTION(BlueprintCallable, Category = "RTS|Project|Dev")
	FGardenFervorProjectId SmokeStartLevelPadNear(
		FVector Center,
		FString& OutMessage,
		bool bEnsureUnits = true,
		float HalfExtentXY = 600.f);

	/**
	 * C4 dedicated smoke: Intention → Draft WorkSite Project near Center.
	 * Does NOT expand WorkSite, activate, spawn units, spend, or terraform.
	 */
	UFUNCTION(BlueprintCallable, Category = "RTS|Project|Dev")
	FGardenFervorProjectId SmokeStartCohortIntentionNear(
		FVector Center,
		FString& OutMessage,
		float HalfExtentXY = 600.f);

	UFUNCTION(BlueprintPure, Category = "RTS|Project|Dev")
	FGardenFervorProjectId GetLastSmokeProjectId() const { return LastSmokeProjectId; }

	UFUNCTION(BlueprintPure, Category = "RTS|Project|Dev")
	FGardenFervorProjectId GetLastCohortIntentionProjectId() const { return LastCohortIntentionProjectId; }

	/** Short HUD line: project status + task progress for LastSmokeProjectId. */
	UFUNCTION(BlueprintPure, Category = "RTS|Project|Dev")
	FString GetSmokeStatusLine() const;

	/** C4 smoke line: intention → project id/status (no PE / FWSG). */
	UFUNCTION(BlueprintPure, Category = "RTS|Project|Dev")
	FString GetCohortIntentionStatusLine() const;

	/**
	 * C5 — mark construction Complete (Achevé). Distinct from En service.
	 * Re-evaluates S3 service criterion (Stock B Timber). Does not spend or expand.
	 */
	UFUNCTION(BlueprintCallable, Category = "RTS|Project|Service")
	bool MarkConstructionComplete(FGardenFervorProjectId ProjectId);

	/** C5 — refresh bInService from Complete + Stock B Timber (no consume). */
	UFUNCTION(BlueprintCallable, Category = "RTS|Project|Service")
	bool RefreshCohortServiceState(FGardenFervorProjectId ProjectId);

	UFUNCTION(BlueprintPure, Category = "RTS|Project|Service")
	bool IsConstructionComplete(FGardenFervorProjectId ProjectId) const;

	UFUNCTION(BlueprintPure, Category = "RTS|Project|Service")
	bool IsInService(FGardenFervorProjectId ProjectId) const;

	/**
	 * C5 smoke: Complete without Timber → not En service; Deposit Timber on B → En service.
	 * Does not run Extract/Transport/Build gameplay. Does not consume Timber after Deposit.
	 */
	UFUNCTION(BlueprintCallable, Category = "RTS|Project|Dev")
	FGardenFervorProjectId SmokeDemonstrateCohortServiceNear(
		FVector Center,
		FString& OutMessage,
		float HalfExtentXY = 600.f);

	UFUNCTION(BlueprintPure, Category = "RTS|Project|Dev")
	FString GetCohortServiceStatusLine() const;

protected:
	/** Legacy LevelPad Spoil→Fill→Raise planner (historical consumer). */
	int32 ExpandLevelPad(FGardenFervorProjectRecord& Project, UGardenFervorTaskSubsystem* Tasks);

	/**
	 * C3 generic WorkSite expand (Cas A): apply SitePrep params, ensure stocks A/B,
	 * no Terraform / ExpandForest / Extract-Transport-Build chain in T5.
	 */
	int32 ExpandWorkSite(FGardenFervorProjectRecord& Project, UGardenFervorTaskSubsystem* Tasks);

	FGardenFervorProjectRecord* FindMutable(int32 Id);
	const FGardenFervorProjectRecord* FindConst(int32 Id) const;

	int32 NextProjectId = 1;
	TMap<int32, FGardenFervorProjectRecord> Projects;
	FGardenFervorProjectId LastSmokeProjectId;
	FGardenFervorProjectId LastCohortIntentionProjectId;
	FGardenFervorProjectId LastCohortServiceProjectId;
};
