// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CyberRushGameMode.generated.h"

UCLASS(minimalapi)
class ACyberRushGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	ACyberRushGameMode();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFloorTile> StartTileClass;
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class AFloorTile>> TileClasses;

	FTransform NextSpawnPoint = FTransform::Identity;
	
	void AddFloorTile();

	void AddScore(int32 Point);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentScore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HighScore = 0;

	UPROPERTY(BlueprintReadWrite, Category="UI")
    UUserWidget* MainWidgetInstance;

	UPROPERTY(EditAnywhere)
	FString SaveSlotName = TEXT("HighScore");

	UPROPERTY(EditAnywhere)
	int32 UserIndex = 0;
	
	void SaveGameData();
	void LoadGameData();

	void PlayerDied(AController* PlayerController);
};



