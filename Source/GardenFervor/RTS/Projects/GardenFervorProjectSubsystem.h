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

	UFUNCTION(BlueprintPure, Category = "RTS|Project|Dev")
	FGardenFervorProjectId GetLastSmokeProjectId() const { return LastSmokeProjectId; }

	/** Short HUD line: project status + task progress for LastSmokeProjectId. */
	UFUNCTION(BlueprintPure, Category = "RTS|Project|Dev")
	FString GetSmokeStatusLine() const;

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
};
