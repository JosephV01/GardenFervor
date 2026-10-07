// Copyright Epic Games, Inc. All Rights Reserved.

#include "GardenFervorInvestorDemoPlayerController.h"

#include "GardenFervorSelectionComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"

AGardenFervorInvestorDemoPlayerController::AGardenFervorInvestorDemoPlayerController()
{
	// Selection only — no BuildingPlacement (BeginPlace / TrySpend path).
	SelectionComponent = CreateDefaultSubobject<UGardenFervorSelectionComponent>(TEXT("SelectionComponent"));
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AGardenFervorInvestorDemoPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetWidgetToFocus(nullptr);
	SetInputMode(InputMode);

	// Intentionally no FWSG CreateHUD / BuildMenu / Ages / LevelPad.
}

void AGardenFervorInvestorDemoPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (!SelectionComponent || !IsLocalController())
	{
		return;
	}

	const bool bShift = IsInputKeyDown(EKeys::LeftShift) || IsInputKeyDown(EKeys::RightShift);
	FVector2D MousePos = FVector2D::ZeroVector;
	const bool bHasMouse = GetMouseViewportPosition(MousePos);

	if (bHasMouse)
	{
		if (WasInputKeyJustPressed(EKeys::LeftMouseButton))
		{
			SelectionComponent->BeginSelectGesture(MousePos, bShift);
		}

		if (SelectionComponent->IsMarqueeActive())
		{
			SelectionComponent->UpdateSelectGesture(MousePos);
			if (WasInputKeyJustReleased(EKeys::LeftMouseButton))
			{
				SelectionComponent->EndSelectGesture(MousePos, bShift);
			}
		}
	}
	else if (SelectionComponent->IsMarqueeActive() && WasInputKeyJustReleased(EKeys::LeftMouseButton))
	{
		SelectionComponent->EndSelectGesture(MousePos, bShift);
	}

	if (WasInputKeyJustPressed(EKeys::RightMouseButton))
	{
		SelectionComponent->HandleCommandClick();
	}
	else if (WasInputKeyJustPressed(EKeys::Escape))
	{
		if (SelectionComponent->IsMarqueeActive())
		{
			SelectionComponent->CancelSelectGesture();
		}
		SelectionComponent->ClearSelection();
	}
}

bool AGardenFervorInvestorDemoPlayerController::GetMouseViewportPosition(FVector2D& OutPos) const
{
	if (SelectionComponent)
	{
		return SelectionComponent->GetMouseViewportPos(OutPos);
	}
	OutPos = UWidgetLayoutLibrary::GetMousePositionOnViewport(
		const_cast<AGardenFervorInvestorDemoPlayerController*>(this));
	return true;
}
