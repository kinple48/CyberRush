// Copyright Epic Games, Inc. All Rights Reserved.

#include "CyberRushGameMode.h"
#include "CyberRushCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "LJW/CyberRushSaveGame.h"
#include "LJW/FloorTile.h"
#include "LJW/FloorTileType1.h"
#include "LJW/FloorTileType2.h"
#include "LJW/MainPlayerController.h"
#include "LJW/Obstacle.h"
#include "LJW/EnemyBase.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HHS/RunnerPlayerBase.h"
#include "HHS/PlayerMoveComponent.h"


ACyberRushGameMode::ACyberRushGameMode()
{
	PlayerControllerClass = AMainPlayerController::StaticClass();
}

void ACyberRushGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC)
	{
		APawn* PlayerPawn = PC->GetPawn();
		if (PlayerPawn)
		{
			RunnerCharacterRef = Cast<ARunnerPlayerBase>(PlayerPawn);
		}
	}

	NextSpawnPoint.SetLocation(FVector(0, 0, 0));
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

	GetWorld()->GetTimerManager().SetTimer(
		RunStartDelayHandle,
		this,
		&ACyberRushGameMode::EnableRunning,
		3.0f,
		false
	);
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
		if (AFloorTileType1* TileType1 = Cast<AFloorTileType1>(FloorTile))
		{
			TileType1->SpawnItemLine();
		}
		else if (AFloorTileType2* TileType2 = Cast<AFloorTileType2>(FloorTile))
		{
			TileType2->SpawnObjectLine();
		}
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
	APawn* DeadPawn = PlayerController->GetPawn();
	if (DeadPawn)
	{
		DeadPawn->Destroy();
	}
}

void ACyberRushGameMode::RestartGameState()
{
	CurrentScore = 0;
	// Destroy FloorTile
	for (TActorIterator<AFloorTile> It(GetWorld()); It; ++It)
	{
		It->Destroy();
	}

	// Destroy Enemy
	for (TActorIterator<AEnemyBase> It(GetWorld()); It; ++It)
	{
		It->Destroy();
	}

	// Destroy Obstacle
	for (TActorIterator<AObstacle> It(GetWorld()); It; ++It)
	{
		It->Destroy();
	}

	NextSpawnPoint.SetLocation(FVector::ZeroVector);
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

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC)
	{
		if (APawn* OldPawn = PC->GetPawn())
		{
			OldPawn->Destroy();
		}

		FVector SpawnLocation(300.f, 0.f, 0.f);
		FRotator SpawnRotation = FRotator::ZeroRotator;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = PC;
		SpawnParams.Instigator = PC->GetPawn();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		APawn* NewPawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, SpawnLocation, SpawnRotation, SpawnParams);
		if (NewPawn)
		{
			PC->Possess(NewPawn);
		}
		RunnerCharacterRef = Cast<ARunnerPlayerBase>(NewPawn);
	}
	RunnerCharacterRef->MoveComp->bCanRun = false;
	RunnerCharacterRef->bIsDead = false;
	GetWorld()->GetTimerManager().SetTimer(
		RunStartDelayHandle,
		this,
		&ACyberRushGameMode::EnableRunning,
		3.0f,
		false
	);
	
}

void ACyberRushGameMode::EnableRunning()
{
	if (!RunnerCharacterRef) return;
	RunnerCharacterRef->MoveComp->bCanRun = true;
}