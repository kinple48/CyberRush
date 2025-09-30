// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CYBERRUSH_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PlayerAnim)
	float Speed = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PlayerAnim)
	bool IsInAir;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PlayerAnim)
	bool isDead = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PlayerAnim)
	bool isRun = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PlayerAnim)
	class UAnimMontage* PlayerMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PlayerAnim)
	bool isAttack = false;
	
	UFUNCTION()
	void AnimNotify_Move_L_Start();

	UFUNCTION()
	void AnimNotify_Move_L_End();

	UFUNCTION()
	void AnimNotify_Move_R_Start();

	UFUNCTION()
	void AnimNotify_Move_R_End();

	UFUNCTION()
	void AnimNotify_footstep1();

	UFUNCTION()
	void AnimNotify_footstep2();
};
