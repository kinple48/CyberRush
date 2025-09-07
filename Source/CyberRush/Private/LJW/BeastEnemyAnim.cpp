// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/BeastEnemyAnim.h"

#include "LJW/BeastEnemy.h"

void UBeastEnemyAnim::AnimNotify_DieEnd()
{
	if (ABeastEnemy* enemy = Cast<ABeastEnemy>(TryGetPawnOwner()))
	{
			enemy->FSM->onDieEnd();
	}
}
