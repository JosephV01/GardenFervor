// Copyright Epic Games, Inc. All Rights Reserved.

#include "GardenFervorInvestorDemoLaunchWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"

void UGardenFervorInvestorDemoLaunchWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	if (UWidget* Root = GetRootWidget())
	{
		Root->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	if (LaunchButton && !LaunchButton->OnClicked.IsAlreadyBound(this, &ThisClass::HandleLaunchClicked))
	{
		LaunchButton->OnClicked.AddDynamic(this, &ThisClass::HandleLaunchClicked);
	}
}

TSharedRef<SWidget> UGardenFervorInvestorDemoLaunchWidget::RebuildWidget()
{
	if (!WidgetTree->RootWidget)
	{
		UCanvasPanel* Canvas = WidgetTree->ConstructWidget<UCanvasPanel>(
			UCanvasPanel::StaticClass(), TEXT("DemoLaunchCanvas"));
		Canvas->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		USizeBox* Size = WidgetTree->ConstructWidget<USizeBox>(
			USizeBox::StaticClass(), TEXT("DemoLaunchSize"));
		Size->SetWidthOverride(360.f);
		Size->SetHeightOverride(52.f);
		Size->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		UButton* Button = WidgetTree->ConstructWidget<UButton>(
			UButton::StaticClass(), TEXT("DemoLaunchButton"));
		FButtonStyle Style = Button->GetStyle();
		Style.Normal.TintColor = FSlateColor(FLinearColor(0.08f, 0.28f, 0.18f, 0.92f));
		Style.Hovered.TintColor = FSlateColor(FLinearColor(0.12f, 0.42f, 0.26f, 0.95f));
		Style.Pressed.TintColor = FSlateColor(FLinearColor(0.05f, 0.18f, 0.12f, 0.95f));
		Style.Disabled.TintColor = FSlateColor(FLinearColor(0.08f, 0.08f, 0.08f, 0.4f));
		Button->SetStyle(Style);
		Button->SetVisibility(ESlateVisibility::Visible);
		LaunchButton = Button;
		Size->AddChild(Button);

		UTextBlock* Label = WidgetTree->ConstructWidget<UTextBlock>(
			UTextBlock::StaticClass(), TEXT("DemoLaunchLabel"));
		FSlateFontInfo Font = Label->GetFont();
		Font.Size = 16;
		Label->SetFont(Font);
		Label->SetColorAndOpacity(FSlateColor(FLinearColor(0.95f, 1.f, 0.9f)));
		Label->SetJustification(ETextJustify::Center);
		Label->SetText(FText::FromString(TEXT("LANCER LA DÉMONSTRATION")));
		Label->SetVisibility(ESlateVisibility::HitTestInvisible);
		LaunchLabel = Label;
		Button->AddChild(Label);

		UCanvasPanelSlot* CanvasSlot = Canvas->AddChildToCanvas(Size);
		CanvasSlot->SetAnchors(FAnchors(0.5f, 1.f, 0.5f, 1.f)); // bottom-center
		CanvasSlot->SetAlignment(FVector2D(0.5f, 1.f));
		CanvasSlot->SetPosition(FVector2D(0.f, -36.f));
		CanvasSlot->SetAutoSize(true);
		CanvasSlot->SetZOrder(10);

		WidgetTree->RootWidget = Canvas;
	}

	return Super::RebuildWidget();
}

void UGardenFervorInvestorDemoLaunchWidget::HandleLaunchClicked()
{
	OnLaunchClicked.Broadcast();
}

void UGardenFervorInvestorDemoLaunchWidget::SetLaunchVisible(bool bVisible)
{
	if (bVisible)
	{
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		if (LaunchButton)
		{
			LaunchButton->SetIsEnabled(true);
			LaunchButton->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		if (LaunchButton)
		{
			LaunchButton->SetIsEnabled(false);
			LaunchButton->SetVisibility(ESlateVisibility::Collapsed);
		}
		SetVisibility(ESlateVisibility::Collapsed);
	}
}
