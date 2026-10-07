// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GardenFervorInvestorDemoPlayerController.generated.h"

class UGardenFervorSelectionComponent;
class UGardenFervorInvestorDemoLaunchWidget;

/**
 * Investor Demo — RTS control without FWSG HUD / BeginPlace / Ages UI.
 * No CreateHUD. Presentation layer only (P0 isolation).
 */
UCLASS()
class GARDENFERVOR_API AGardenFervorInvestorDemoPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGardenFervorInvestorDemoPlayerController();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "RTS|Selection")
	UGardenFervorSelectionComponent* GetSelectionComponent() const { return SelectionComponent; }

	bool GetMouseViewportPosition(FVector2D& OutPos) const;

	/** One-shot: same entry as gf.InvestorDemo.RunS3 / F8. */
	UFUNCTION(Exec, Category = "RTS|InvestorDemo")
	void InvestorDemoRunS3();

	/** Called when S3 starts (button / F8 / console) so the launch button hides. */
	void NotifyDemoS3Started();

protected:
	void EnsureLaunchWidget();
	void HideLaunchWidget();

	UFUNCTION()
	void HandleLaunchButtonClicked();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RTS|Selection")
	TObjectPtr<UGardenFervorSelectionComponent> SelectionComponent;

	UPROPERTY()
	TObjectPtr<UGardenFervorInvestorDemoLaunchWidget> LaunchWidget;

	bool bInvestorDemoS3Ran = false;
};
