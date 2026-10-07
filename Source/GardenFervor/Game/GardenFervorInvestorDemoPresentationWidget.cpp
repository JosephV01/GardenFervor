// Copyright Epic Games, Inc. All Rights Reserved.

#include "GardenFervorInvestorDemoPresentationWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

namespace InvestorDemoOverlayPrivate
{
	static constexpr float PanelMaxWidth = 340.f;
	static constexpr float EdgePad = 14.f;
}

void UGardenFervorInvestorDemoPresentationWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::HitTestInvisible);
	if (UWidget* Root = GetRootWidget())
	{
		Root->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

TSharedRef<SWidget> UGardenFervorInvestorDemoPresentationWidget::RebuildWidget()
{
	if (!WidgetTree->RootWidget)
	{
		// Transparent full-screen host — does NOT paint over the scene.
		UCanvasPanel* Canvas = WidgetTree->ConstructWidget<UCanvasPanel>(
			UCanvasPanel::StaticClass(), TEXT("DemoOverlayCanvas"));
		Canvas->SetVisibility(ESlateVisibility::HitTestInvisible);

		USizeBox* Size = WidgetTree->ConstructWidget<USizeBox>(
			USizeBox::StaticClass(), TEXT("DemoOverlaySize"));
		Size->SetWidthOverride(InvestorDemoOverlayPrivate::PanelMaxWidth);
		Size->SetVisibility(ESlateVisibility::HitTestInvisible);

		UBorder* Panel = WidgetTree->ConstructWidget<UBorder>(
			UBorder::StaticClass(), TEXT("DemoOverlayPanel"));
		Panel->SetPadding(FMargin(10.f, 8.f));
		Panel->SetBrushColor(FLinearColor(0.02f, 0.045f, 0.07f, 0.72f));
		Panel->SetVisibility(ESlateVisibility::HitTestInvisible);
		PanelBorder = Panel;
		Size->AddChild(Panel);

		UVerticalBox* Column = WidgetTree->ConstructWidget<UVerticalBox>(
			UVerticalBox::StaticClass(), TEXT("DemoOverlayColumn"));
		Panel->SetContent(Column);

		StepText = MakeLabel(TEXT("DemoStep"), FLinearColor(1.f, 0.95f, 0.55f), 14);
		Column->AddChild(StepText);

		ProgressText = MakeLabel(TEXT("DemoProgress"), FLinearColor(0.55f, 0.75f, 0.65f), 11);
		Column->AddChild(ProgressText);

		StatusText = MakeLabel(TEXT("DemoStatus"), FLinearColor(0.9f, 0.93f, 0.96f), 12);
		Column->AddChild(StatusText);

		PeText = MakeLabel(TEXT("DemoPe"), FLinearColor(0.55f, 0.95f, 0.75f), 12);
		Column->AddChild(PeText);

		if (UVerticalBoxSlot* StepSlot = Cast<UVerticalBoxSlot>(StepText->Slot))
		{
			StepSlot->SetPadding(FMargin(0.f, 0.f, 0.f, 2.f));
		}
		if (UVerticalBoxSlot* ProgressSlot = Cast<UVerticalBoxSlot>(ProgressText->Slot))
		{
			ProgressSlot->SetPadding(FMargin(0.f, 0.f, 0.f, 4.f));
		}
		if (UVerticalBoxSlot* StatusSlot = Cast<UVerticalBoxSlot>(StatusText->Slot))
		{
			StatusSlot->SetPadding(FMargin(0.f, 0.f, 0.f, 3.f));
		}

		UCanvasPanelSlot* CanvasSlot = Canvas->AddChildToCanvas(Size);
		CanvasSlot->SetAnchors(FAnchors(0.f, 0.f, 0.f, 0.f)); // top-left
		CanvasSlot->SetAlignment(FVector2D(0.f, 0.f));
		CanvasSlot->SetPosition(FVector2D(
			InvestorDemoOverlayPrivate::EdgePad,
			InvestorDemoOverlayPrivate::EdgePad));
		CanvasSlot->SetAutoSize(true);
		CanvasSlot->SetZOrder(0);

		WidgetTree->RootWidget = Canvas;
	}

	return Super::RebuildWidget();
}

UTextBlock* UGardenFervorInvestorDemoPresentationWidget::MakeLabel(
	const FName& Name, const FLinearColor& Color, int32 FontSize)
{
	UTextBlock* Text = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), Name);
	FSlateFontInfo Font = Text->GetFont();
	Font.Size = FontSize;
	Text->SetFont(Font);
	Text->SetColorAndOpacity(FSlateColor(Color));
	Text->SetVisibility(ESlateVisibility::HitTestInvisible);
	Text->SetAutoWrapText(true);
	return Text;
}

void UGardenFervorInvestorDemoPresentationWidget::SetPresentationState(
	int32 StepIndex,
	int32 StepCount,
	const FString& StepTitle,
	const FString& DetailLine,
	const FString& PeLine,
	bool bConcluded,
	bool bSucceeded)
{
	const int32 SafeCount = FMath::Max(StepCount, 1);
	const int32 SafeIndex = FMath::Clamp(StepIndex, 0, SafeCount);

	FString Bars;
	Bars.Reserve(SafeCount);
	for (int32 i = 1; i <= SafeCount; ++i)
	{
		Bars += (i <= SafeIndex) ? TEXT("●") : TEXT("○");
	}

	if (StepText)
	{
		StepText->SetText(FText::FromString(
			FString::Printf(TEXT("%d/%d  %s"), SafeIndex, SafeCount, *StepTitle)));
		StepText->SetColorAndOpacity(FSlateColor(
			bConcluded
				? (bSucceeded ? FLinearColor(0.3f, 1.f, 0.5f) : FLinearColor(1.f, 0.5f, 0.3f))
				: FLinearColor(1.f, 0.95f, 0.55f)));
	}
	if (ProgressText)
	{
		ProgressText->SetText(FText::FromString(Bars));
	}
	if (StatusText)
	{
		if (bConcluded)
		{
			StatusText->SetText(FText::FromString(
				bSucceeded
					? TEXT("Intention → unités autonomes → En service")
					: (DetailLine.IsEmpty() ? TEXT("Parcours incomplet") : DetailLine)));
			StatusText->SetColorAndOpacity(FSlateColor(
				bSucceeded ? FLinearColor(0.3f, 1.f, 0.5f) : FLinearColor(1.f, 0.55f, 0.3f)));
		}
		else if (!DetailLine.IsEmpty() && DetailLine != TEXT(" "))
		{
			FString Short = DetailLine;
			if (Short.Len() > 56)
			{
				Short = Short.Left(54) + TEXT("…");
			}
			StatusText->SetText(FText::FromString(Short));
			StatusText->SetColorAndOpacity(FSlateColor(FLinearColor(0.9f, 0.93f, 0.96f)));
		}
		else
		{
			StatusText->SetText(FText::FromString(TEXT("Suivez la scène")));
			StatusText->SetColorAndOpacity(FSlateColor(FLinearColor(0.6f, 0.7f, 0.75f)));
		}
	}
	if (PeText)
	{
		PeText->SetText(FText::FromString(PeLine.IsEmpty() ? TEXT("Bois A=…  B=…") : PeLine));
	}
	if (PanelBorder)
	{
		PanelBorder->SetBrushColor(
			bConcluded && bSucceeded
				? FLinearColor(0.02f, 0.14f, 0.07f, 0.78f)
				: FLinearColor(0.02f, 0.045f, 0.07f, 0.72f));
	}
}
