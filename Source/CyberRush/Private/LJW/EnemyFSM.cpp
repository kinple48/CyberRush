// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/EnemyFSM.h"

#include "HHS/RunnerPlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "LJW/EnemyAnim.h"
#include "LJW/EnemyBase.h"

// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();
	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), ARunnerPlayerBase::StaticClass());
	if (actor)
	{
		target = Cast<ARunnerPlayerBase>(actor);
	}

	me = Cast<AEnemyBase>(GetOwner());
	if (me)
	{
		Anim = Cast<UEnemyAnim>(me->GetMesh()->GetAnimInstance());
	}
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (mState)
	{
	case EEnemyState::Idle:
		IdleState();
		break;
	case EEnemyState::Move:
		MoveState();
		break;
	case EEnemyState::Damage:
		DamageState();
		break;
	case EEnemyState::Die:
		DieState();
		break;
	}
	
}

void UEnemyFSM::IdleState()
{
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime >= IdleDelayTime)
	{
		mState = EEnemyState::Move;
		CurrentTime = 0.0f;
		Anim->AnimState = mState;
	}
}

void UEnemyFSM::MoveState()
{
	if (!target || !me) return;
	
	FVector Destination = target->GetActorLocation();
	FVector Dir = Destination - me->GetActorLocation();
	me->AddMovementInput(Dir);
}

void UEnemyFSM::DamageState()
{
	CurrentTime += GetWorld()->DeltaTimeSeconds;

	if (CurrentTime > damageDelayTime)
	{
		mState = EEnemyState::Idle;
		CurrentTime = 0.0f;
		Anim->AnimState = mState;
	}
}

void UEnemyFSM::DieState()
{
}

void UEnemyFSM::OnDamageProcess()
{
	hp--;

	if (hp > 0)
	{
		mState = EEnemyState::Damage;
	}
	else
	{
		mState = EEnemyState::Die;
	}
	Anim->AnimState = mState;
}

