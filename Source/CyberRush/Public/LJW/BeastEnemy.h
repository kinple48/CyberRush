// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "GameFramework/Character.h"
#include "BeastEnemy.generated.h"

UCLASS()
class CYBERRUSH_API ABeastEnemy : public AEnemyBase
{
	GENERATED_BODY()

public:
	ABeastEnemy();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
