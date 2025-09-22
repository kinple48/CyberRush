#include "LJW/BeastEnemyFSM.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HHS/RunnerPlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "LJW/BeastEnemy.h"
#include "LJW/BeastEnemyAnim.h"
#include "Components/SphereComponent.h"
#include "LJW/Magazine.h"

UBeastEnemyFSM::UBeastEnemyFSM()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UBeastEnemyFSM::BeginPlay()
{
	Super::BeginPlay();
	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), ARunnerPlayerBase::StaticClass());
	if (actor)
	{
		target = Cast<ARunnerPlayerBase>(actor);
	}
	me = Cast<ABeastEnemy>(GetOwner());
	if (me)
	{
		Anim = Cast<UBeastEnemyAnim>(me->GetMesh()->GetAnimInstance());
	}
}

void UBeastEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	switch (mstate)
	{
		case EEnemyState::Idle: {IdleState();} break;
		case EEnemyState::Move: {MoveState();} break;
		case EEnemyState::Damage: {DamageState();} break;
		case EEnemyState::Die: {DieState();} break;
	}
}

void UBeastEnemyFSM::IdleState()
{
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime >= IdleDelayTime)
	{
		mstate = EEnemyState::Move;
		CurrentTime = 0;
		Anim->AnimState = mstate;
	}
}

void UBeastEnemyFSM::MoveState()
{
	if (!target || !me) return;

	FVector destination = target->GetActorLocation();
	FVector dir = destination - me->GetActorLocation();

	FVector currentVelocity = me->GetCharacterMovement()->Velocity;
	me -> AddMovementInput(dir);
}

void UBeastEnemyFSM::DamageState()
{
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime >= damageDelayTime)
	{
		mstate = EEnemyState::Idle;
		CurrentTime = 0;
		Anim->AnimState = mstate;
	}
}

void UBeastEnemyFSM::DieState()
{
	if (!bDieDone) return;
}

void UBeastEnemyFSM::OnDamageProcess(int32 damage)
{
	hp -= damage;
	if (hp > 0)
	{
		mstate = EEnemyState::Damage;
		int32 randValue = FMath::RandRange(0, 1);
		FString sectionName = FString::Printf(TEXT("Damage%d"),randValue);
		me->PlayAnimMontage(Anim->EnemyMontage,1.f,FName(*sectionName));
	}
	else
	{
		mstate = EEnemyState::Die;
		me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		me->CollisionRange->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		me->PlayAnimMontage(Anim->EnemyMontage, 1.f,TEXT("Die"));
		const float DropChance = 0.3f; // 30%
		if (FMath::FRand() <= DropChance && MagazineFactory)
		{
			FVector SpawnLocation = me->GetActorLocation();
			FRotator SpawnRotation = FRotator::ZeroRotator;
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			GetWorld()->SpawnActor<AMagazine>(MagazineFactory, SpawnLocation, SpawnRotation, SpawnParams);
		}
		
	}
	Anim->AnimState = mstate;
}