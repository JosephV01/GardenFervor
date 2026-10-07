// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GardenFervorInvestorDemoGameMode.generated.h"

/**
 * Investor Demo — minimal RTS host.
 * No AoE boot: no TownCenter, Worker, ResourceNodes, FWSG init, Ages.
 * Does not alter AGardenFervorGameMode (Island).
 */
UCLASS()
class GARDENFERVOR_API AGardenFervorInvestorDemoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGardenFervorInvestorDemoGameMode();

	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual APlayerController* SpawnPlayerController(ENetRole InRemoteRole, const FString& Options) override;

protected:
	void InjectPlayerInputComponent(APlayerController* PlayerController) const;
};
