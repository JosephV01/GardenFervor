// Copyright Epic Games, Inc. All Rights Reserved.

#include "GardenFervorInvestorDemoS3Bridge.h"

#include "GardenFervorInvestorDemoS3Director.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "HAL/IConsoleManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogGardenFervorInvestorDemoS3, Log, All);

bool FGardenFervorInvestorDemoS3Bridge::RunS3CasA(UWorld* World, FString& OutMessage)
{
	OutMessage.Reset();
	if (!World)
	{
		OutMessage = TEXT("InvestorDemo S3: no world");
		return false;
	}

	AGardenFervorInvestorDemoS3Director* Director = nullptr;
	for (TActorIterator<AGardenFervorInvestorDemoS3Director> It(World); It; ++It)
	{
		Director = *It;
		break;
	}
	if (!Director)
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Director = World->SpawnActor<AGardenFervorInvestorDemoS3Director>(
			AGardenFervorInvestorDemoS3Director::StaticClass(),
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			Params);
	}
	if (!Director)
	{
		OutMessage = TEXT("InvestorDemo S3: failed to spawn presentation director");
		return false;
	}
	if (Director->IsRunning())
	{
		OutMessage = TEXT("InvestorDemo S3: presentation already running");
		return false;
	}

	Director->StartPresentation();
	OutMessage = TEXT("InvestorDemo S3: presentation started — watch PH/labels/units (async). Final ok= logged when En service.");
	UE_LOG(LogGardenFervorInvestorDemoS3, Display, TEXT("%s"), *OutMessage);
	return true;
}

void FGardenFervorInvestorDemoS3Bridge::RefreshPlaceholderLabels(
	UWorld* World,
	FGardenFervorProjectId ProjectId)
{
	// Presentation owned by AGardenFervorInvestorDemoS3Director during the run.
	(void)World;
	(void)ProjectId;
}

static FAutoConsoleCommandWithWorld GGardenFervorInvestorDemoRunS3Cmd(
	TEXT("gf.InvestorDemo.RunS3"),
	TEXT("Investor Demo étape 3: start async S3 Cas A T1→T9 presentation (PE live)"),
	FConsoleCommandWithWorldDelegate::CreateLambda([](UWorld* World)
	{
		FString Msg;
		const bool bOk = FGardenFervorInvestorDemoS3Bridge::RunS3CasA(World, Msg);
		UE_LOG(LogGardenFervorInvestorDemoS3, Display, TEXT("gf.InvestorDemo.RunS3 started=%d · %s"), bOk ? 1 : 0, *Msg);
	}));
