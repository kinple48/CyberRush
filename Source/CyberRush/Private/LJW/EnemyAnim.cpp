// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/EnemyAnim.h"

#include "LJW/EnemyBase.h"


void UEnemyAnim::AnimNotify_DieEnd()
{
	if (AEnemyBase* enemy = Cast<AEnemyBase>(TryGetPawnOwner()))
	{
		enemy->FSM->onDieEnd();
	}
}
