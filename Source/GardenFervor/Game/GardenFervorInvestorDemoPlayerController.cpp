// Copyright Epic Games, Inc. All Rights Reserved.

#include "GardenFervorInvestorDemoPlayerController.h"

#include "GardenFervorInvestorDemoLaunchWidget.h"
#include "GardenFervorInvestorDemoS3Bridge.h"
#include "GardenFervorSelectionComponent.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogGardenFervorInvestorDemoPC, Log, All);

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

	EnsureLaunchWidget();

	// Intentionally no FWSG CreateHUD / BuildMenu / Ages / LevelPad.
	UE_LOG(LogGardenFervorInvestorDemoPC, Log,
		TEXT("InvestorDemo PC ready — bouton / F8 / gf.InvestorDemo.RunS3"));
}

void AGardenFervorInvestorDemoPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	HideLaunchWidget();
	if (LaunchWidget)
	{
		LaunchWidget->RemoveFromParent();
		LaunchWidget = nullptr;
	}
	Super::EndPlay(EndPlayReason);
}

void AGardenFervorInvestorDemoPlayerController::EnsureLaunchWidget()
{
	if (LaunchWidget || !IsLocalController())
	{
		return;
	}

	LaunchWidget = CreateWidget<UGardenFervorInvestorDemoLaunchWidget>(
		this, UGardenFervorInvestorDemoLaunchWidget::StaticClass());
	if (!LaunchWidget)
	{
		return;
	}

	LaunchWidget->AddToViewport(40);
	LaunchWidget->SetLaunchVisible(true);
	if (!LaunchWidget->OnLaunchClicked.IsAlreadyBound(this, &ThisClass::HandleLaunchButtonClicked))
	{
		LaunchWidget->OnLaunchClicked.AddDynamic(this, &ThisClass::HandleLaunchButtonClicked);
	}
}

void AGardenFervorInvestorDemoPlayerController::HideLaunchWidget()
{
	if (LaunchWidget)
	{
		LaunchWidget->SetLaunchVisible(false);
	}
}

void AGardenFervorInvestorDemoPlayerController::HandleLaunchButtonClicked()
{
	InvestorDemoRunS3();
}

void AGardenFervorInvestorDemoPlayerController::NotifyDemoS3Started()
{
	bInvestorDemoS3Ran = true;
	HideLaunchWidget();
}

void AGardenFervorInvestorDemoPlayerController::InvestorDemoRunS3()
{
	if (bInvestorDemoS3Ran)
	{
		HideLaunchWidget();
		UE_LOG(LogGardenFervorInvestorDemoPC, Warning,
			TEXT("InvestorDemo S3 already started this session (one-shot)"));
		return;
	}

	FString Msg;
	const bool bStarted = FGardenFervorInvestorDemoS3Bridge::RunS3CasA(GetWorld(), Msg);
	if (bStarted)
	{
		NotifyDemoS3Started();
	}
	UE_LOG(LogGardenFervorInvestorDemoPC, Display, TEXT("%s"), *Msg);
}

void AGardenFervorInvestorDemoPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (!IsLocalController())
	{
		return;
	}

	if (WasInputKeyJustPressed(EKeys::F8))
	{
		InvestorDemoRunS3();
	}

	if (!SelectionComponent)
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
