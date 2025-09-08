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

	// Y 라인 위치 배열
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TArray<float> LaneYPositions = { -250.f, 0.f, 250.f };

	// 아이템 개수
	UPROPERTY(EditAnywhere, Category = "Spawning")
	int32 ItemCount = 4;

	// 아이템 간 거리
	UPROPERTY(EditAnywhere, Category = "Spawning")
	float ItemSpacing = 100.f;

	// 실제 스폰 함수
	UFUNCTION(BlueprintCallable)
	void SpawnItemLine();
};
