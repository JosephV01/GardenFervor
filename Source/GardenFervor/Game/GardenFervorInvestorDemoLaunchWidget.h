// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GardenFervorInvestorDemoLaunchWidget.generated.h"

class UButton;
class UTextBlock;
class UCanvasPanel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGardenFervorInvestorDemoLaunchClicked);

/**
 * Investor Demo — bouton de lancement uniquement.
 * Déclenche le même mécanisme que gf.InvestorDemo.RunS3 (via le PlayerController).
 */
UCLASS()
class GARDENFERVOR_API UGardenFervorInvestorDemoLaunchWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void SetLaunchVisible(bool bVisible);

	UPROPERTY(BlueprintAssignable, Category = "InvestorDemo")
	FGardenFervorInvestorDemoLaunchClicked OnLaunchClicked;

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

	UFUNCTION()
	void HandleLaunchClicked();

	UPROPERTY()
	TObjectPtr<UButton> LaunchButton = nullptr;
	UPROPERTY()
	TObjectPtr<UTextBlock> LaunchLabel = nullptr;
};
