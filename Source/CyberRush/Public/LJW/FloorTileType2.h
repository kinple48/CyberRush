// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LJW/FloorTile.h"
#include "FloorTileType2.generated.h"

/**
 * 
 */
UCLASS()
class CYBERRUSH_API AFloorTileType2 : public AFloorTile
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AObstacle> ObstacleFactory;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TArray<float> LaneYPositions = { -250.f, 0.f, 250.f };

	UFUNCTION(BlueprintCallable)
	void SpawnObjectLine();
};
