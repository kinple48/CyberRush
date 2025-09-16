// Fill out your copyright notice in the Description page of Project Settings.


#include "HHS/PlayerAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "HHS/PlayerCombatComponent.h"
#include "HHS/PlayerMoveComponent.h"
#include "HHS/RunnerPlayerBase.h"

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	ARunnerPlayerBase* player = Cast<ARunnerPlayerBase>(TryGetPawnOwner());
	if( player == nullptr )
	{
		return;
	}
	
	IsInAir = player->GetCharacterMovement()->IsFalling();
	isDead = player->bIsDead;
	isRun = player->MoveComp->bCanRun;
}

void UPlayerAnimInstance::AnimNotify_Reload()
{
	ARunnerPlayerBase* player = Cast<ARunnerPlayerBase>(TryGetPawnOwner());
	if( player == nullptr )
	{
		return;
	}
	
	isReloading = false;
	player->CombatComp->ReloadGun();
}

void UPlayerAnimInstance::AnimNotify_Move_L_Start()
{
	ARunnerPlayerBase* player = Cast<ARunnerPlayerBase>(TryGetPawnOwner());
	if( player == nullptr )
	{
		return;
	}
	player->CombatComp->isMoving = true;
}

void UPlayerAnimInstance::AnimNotify_Move_L_End()
{
	ARunnerPlayerBase* player = Cast<ARunnerPlayerBase>(TryGetPawnOwner());
	if( player == nullptr )
	{
		return;
	}
	player->CombatComp->isMoving = false;
}

void UPlayerAnimInstance::AnimNotify_Move_R_Start()
{
	ARunnerPlayerBase* player = Cast<ARunnerPlayerBase>(TryGetPawnOwner());
	if( player == nullptr )
	{
		return;
	}
	player->CombatComp->isMoving = true;
}

void UPlayerAnimInstance::AnimNotify_Move_R_End()
{
	ARunnerPlayerBase* player = Cast<ARunnerPlayerBase>(TryGetPawnOwner());
	if( player == nullptr )
	{
		return;
	}
	player->CombatComp->isMoving = false;
}
