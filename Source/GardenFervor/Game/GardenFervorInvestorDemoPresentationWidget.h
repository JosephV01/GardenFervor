// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GardenFervorInvestorDemoPresentationWidget.generated.h"

class UTextBlock;
class UBorder;
class UCanvasPanel;
class USizeBox;

/**
 * Investor Demo — overlay compact (coin écran), pas un HUD gameplay.
 * Étape 5 : titres / statut orientés narration investisseur (sans jargon technique).
 */
UCLASS()
class GARDENFERVOR_API UGardenFervorInvestorDemoPresentationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void SetPresentationState(
		int32 StepIndex,
		int32 StepCount,
		const FString& StepTitle,
		const FString& DetailLine,
		const FString& PeLine,
		bool bConcluded,
		bool bSucceeded);

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

	UTextBlock* MakeLabel(const FName& Name, const FLinearColor& Color, int32 FontSize);

	UPROPERTY()
	TObjectPtr<UBorder> PanelBorder = nullptr;
	UPROPERTY()
	TObjectPtr<UTextBlock> StepText = nullptr;
	UPROPERTY()
	TObjectPtr<UTextBlock> ProgressText = nullptr;
	UPROPERTY()
	TObjectPtr<UTextBlock> PeText = nullptr;
	UPROPERTY()
	TObjectPtr<UTextBlock> StatusText = nullptr;
};
