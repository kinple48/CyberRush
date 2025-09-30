// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DroneEnemyFSM.h"
#include "Animation/AnimInstance.h"
#include "DroneEnemyAnim.generated.h"

/**
 * 
 */
UCLASS()
class CYBERRUSH_API UDroneEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="FSM")
	EDroneState AnimState = EDroneState::Idle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="FSM")
	class UAnimMontage* EnemyMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="FSM")
	bool moveright = true;

	UFUNCTION()
	void AnimNotify_Die();
};
