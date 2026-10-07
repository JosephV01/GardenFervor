// Copyright Epic Games, Inc. All Rights Reserved.

#include "GardenFervorInvestorDemoGameMode.h"

#include "GardenFervorInvestorDemoPlayerController.h"
#include "GardenFervorPlayerInputComponent.h"
#include "GardenFervorStrategyPawn.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogGardenFervorInvestorDemo, Log, All);

AGardenFervorInvestorDemoGameMode::AGardenFervorInvestorDemoGameMode()
{
	DefaultPawnClass = AGardenFervorStrategyPawn::StaticClass();
	PlayerControllerClass = AGardenFervorInvestorDemoPlayerController::StaticClass();
	// Engine PlayerState — no EconomyComponent / TechComponent FWSG.
	PlayerStateClass = APlayerState::StaticClass();
	GameStateClass = AGameStateBase::StaticClass();
}

void AGardenFervorInvestorDemoGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		InjectPlayerInputComponent(It->Get());
	}

	UE_LOG(LogGardenFervorInvestorDemo, Log,
		TEXT("InvestorDemo GameMode ready — no TC/Worker/ResourceNodes/FWSG HUD/Ages boot · étape3: F8 / gf.InvestorDemo.RunS3"));
}

APlayerController* AGardenFervorInvestorDemoGameMode::SpawnPlayerController(
	ENetRole InRemoteRole, const FString& Options)
{
	APlayerController* PC = Super::SpawnPlayerController(InRemoteRole, Options);
	InjectPlayerInputComponent(PC);
	return PC;
}

void AGardenFervorInvestorDemoGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	InjectPlayerInputComponent(NewPlayer);
	// Intentionally no InitializePlayerRTS / SpawnStarterBase / SpawnSampleResourceNodes.
}

void AGardenFervorInvestorDemoGameMode::InjectPlayerInputComponent(APlayerController* PlayerController) const
{
	if (!PlayerController)
	{
		return;
	}
	if (PlayerController->FindComponentByClass<UGardenFervorPlayerInputComponent>())
	{
		return;
	}

	UGardenFervorPlayerInputComponent* GFInput =
		NewObject<UGardenFervorPlayerInputComponent>(PlayerController, TEXT("GardenFervorPlayerInput"));
	GFInput->RegisterComponent();
}
