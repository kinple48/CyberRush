// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LJW/FloorTile.h"
#include "FloorTileType1.generated.h"

UCLASS()
class CYBERRUSH_API AFloorTileType1 : public AFloorTile
{
	GENERATED_BODY()
public:
	AFloorTileType1();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AItem> ItemFactory;
	
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TArray<float> LaneYPositions = { -250.f, 0.f, 250.f };
	
	UFUNCTION(BlueprintCallable)
	void SpawnItemLine();
};
