// Copyright Epic Games, Inc. All Rights Reserved.

#include "CyberRushGameMode.h"
#include "CyberRushCharacter.h"
#include "LocalizationDescriptor.h"
#include "Kismet/GameplayStatics.h"
#include "LJW/CyberRushSaveGame.h"
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
	if (StartTileClass)
	{
		AFloorTile* StartTile = GetWorld()->SpawnActor<AFloorTile>(StartTileClass, NextSpawnPoint);
		if (StartTile)
		{
			NextSpawnPoint = StartTile->GetAttachTransform();
		}
	}
	
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

void ACyberRushGameMode::AddScore(int32 Point)
{
	CurrentScore += Point;
	if (CurrentScore > HighScore)
	{
		HighScore = CurrentScore;
	}
}

void ACyberRushGameMode::SaveGameData()
{
	UCyberRushSaveGame* sg = Cast<UCyberRushSaveGame>(UGameplayStatics::CreateSaveGameObject(UCyberRushSaveGame::StaticClass()));
	sg->HighScoreSave = HighScore;
	UGameplayStatics::SaveGameToSlot(sg, SaveSlotName, UserIndex);
}

void ACyberRushGameMode::LoadGameData()
{
	bool isExist = UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex);
	if (!isExist) return;

	UCyberRushSaveGame* sg = Cast<UCyberRushSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	if (!sg) return;

	HighScore = sg->HighScoreSave;
}

void ACyberRushGameMode::PlayerDied(AController* PlayerController)
{
	if (APlayerController* PC = Cast<APlayerController>(PlayerController))
	{
		if (AMainHUD* MyHUD = Cast<AMainHUD>(PC->GetHUD()))
		{
			MyHUD->ShowGameOverUI();
		}
	}
	APawn* DeadPawn = PlayerController->GetPawn();
	if (DeadPawn)
	{
		DeadPawn->Destroy();
	}
}


