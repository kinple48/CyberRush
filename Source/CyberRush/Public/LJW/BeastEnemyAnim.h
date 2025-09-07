// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeastEnemyFSM.h"
#include "Animation/AnimInstance.h"
#include "BeastEnemyAnim.generated.h"

UCLASS()
class CYBERRUSH_API UBeastEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="FSM")
	EEnemyState AnimState = EEnemyState::Idle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="FSM")
	class UAnimMontage* EnemyMontage;

	UFUNCTION()
	void AnimNotify_DieEnd();
};
