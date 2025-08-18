// Copyright Epic Games, Inc. All Rights Reserved.

#include "CyberRushGameMode.h"
#include "CyberRushCharacter.h"
#include "LJW/FloorTile.h"
#include "LJW/FloorTileType1.h"
#include "LJW/MainHUD.h"
#include "LJW/MainPlayerController.h"
#include "UObject/ConstructorHelpers.h"

ACyberRushGameMode::ACyberRushGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = AMainPlayerController::StaticClass();
	HUDClass = AMainHUD::StaticClass();
}

void ACyberRushGameMode::BeginPlay()
{
	Super::BeginPlay();
	for (int32 i = 0; i < 10; i++)
	{
		AddFloorTile();
	}
}

void ACyberRushGameMode::AddFloorTile()
{
	if (TileClasses.Num() == 0) return;

	int32 RandomIndex = FMath::RandRange(0, TileClasses.Num() - 1);
	TSubclassOf<AFloorTile> TileFactory = TileClasses[RandomIndex];

	AFloorTile* FloorTile = GetWorld()->SpawnActor<AFloorTile>(TileFactory, NextSpawnPoint);
	if (FloorTile)
	{
		NextSpawnPoint = FloorTile->GetAttachTransform();
	}
}
