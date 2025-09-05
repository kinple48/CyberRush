// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/BeastEnemy.h"

#include "LJW/EnemyFSM.h"

ABeastEnemy::ABeastEnemy()
{
	FSM = CreateDefaultSubobject<UEnemyFSM>(TEXT("FSM"));
	/*ConstructorHelpers::FClassFinder<UAnimInstance> tmpAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/LJW/Enemy/BeastEnemy/ABP_BeastEnemy.ABP_BeastEnemy_C'"));
	if (tmpAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(tmpAnim.Class);
	}*/
}

void ABeastEnemy::BeginPlay()
{
	Super::BeginPlay();
}
