// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LJW/FloorTile.h"
#include "FloorTileType3.generated.h"

/**
 * 
 */
UCLASS()
class CYBERRUSH_API AFloorTileType3 : public AFloorTile
{
	GENERATED_BODY()
	
	AFloorTileType3();
	
protected:
	
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* EnemySensor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* EnemySponPoint1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* EnemySponPoint2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* EnemySponPoint3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* EnemySponPoint4;
	
	UFUNCTION()
	void OnSensorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	/*UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyBase> EnemyFactory;*/
	
	void SpawnEnemy();


};
