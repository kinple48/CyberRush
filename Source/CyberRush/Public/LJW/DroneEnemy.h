// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LJW/EnemyBase.h"
#include "DroneEnemy.generated.h"

/**
 * 
 */
UCLASS()
class CYBERRUSH_API ADroneEnemy : public AEnemyBase
{
	GENERATED_BODY()
	ADroneEnemy();

protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSMComponent)
	class UDroneEnemyFSM* FSM;
	
	UPROPERTY(VisibleAnywhere, Category = "Reticle")
	UDecalComponent* ReticleDecal;

	UPROPERTY(EditDefaultsOnly, Category = "Reticle")
	UMaterialInterface* ReticleMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundBase* FireSound;
};
