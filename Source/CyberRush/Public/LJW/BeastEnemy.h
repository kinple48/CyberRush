// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LJW/EnemyBase.h"
#include "BeastEnemy.generated.h"

/**
 * 
 */
UCLASS()
class CYBERRUSH_API ABeastEnemy : public AEnemyBase
{
	GENERATED_BODY()

public:
	ABeastEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	

};
