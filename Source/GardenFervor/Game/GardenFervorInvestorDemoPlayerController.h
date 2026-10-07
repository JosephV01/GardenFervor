// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GardenFervorInvestorDemoPlayerController.generated.h"

class UGardenFervorSelectionComponent;

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
	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "RTS|Selection")
	UGardenFervorSelectionComponent* GetSelectionComponent() const { return SelectionComponent; }

	bool GetMouseViewportPosition(FVector2D& OutPos) const;

	/** Étape 3 — one-shot: run real S3 Cas A T1→T9 path + refresh placeholders. */
	UFUNCTION(Exec, Category = "RTS|InvestorDemo")
	void InvestorDemoRunS3();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RTS|Selection")
	TObjectPtr<UGardenFervorSelectionComponent> SelectionComponent;

	bool bInvestorDemoS3Ran = false;
};
