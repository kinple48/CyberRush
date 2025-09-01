// Fill out your copyright notice in the Description page of Project Settings.


#include "HHS/PlayerAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
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
	//auto movement = player->GetCharacterMovement();
	//if( movement != nullptr )
	//{
	//	IsInAir = movement->IsFalling();
	//}	
}
