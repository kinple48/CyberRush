#include "LJW/BeastEnemyFSM.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HHS/RunnerPlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "LJW/BeastEnemy.h"
#include "LJW/BeastEnemyAnim.h"
#include "Components/SphereComponent.h"

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
	FString logMsg = UEnum::GetValueAsString(mstate);
	//GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Red, logMsg);
	switch (mstate)
	{
		case EEnemyState::Idle: {IdleState();} break;
		case EEnemyState::Move: {MoveState();} break;
		case EEnemyState::Damage: {DamageState();} break;
		case EEnemyState::Die: {DieState();} break;
		case EEnemyState::MoveToLane: {MoveToLane();} break;
		case EEnemyState::Rotate: {RotateState();} break;
		
	}
}

void UBeastEnemyFSM::IdleState()
{
	if (target->bIsDead) return;
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime >= IdleDelayTime)
	{
		mstate = EEnemyState::MoveToLane;
		if (me)
		{
			StartingY = me->GetActorLocation().Y;
		}
		CurrentTime = 0;
		Anim->AnimState = EEnemyState::Move;
	}
}

void UBeastEnemyFSM::MoveState()
{
	if (!target || !me) return;
	if (target->bIsDead)
	{
		mstate = EEnemyState::Idle;
		Anim->AnimState = mstate;
	}
	
	
	FVector dir = me->GetActorForwardVector();

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

void UBeastEnemyFSM::MoveToLane()
{
	if (!me) return;

	float TargetY = 0.0f;
	switch (me->lanenumber)
	{
	case 0: TargetY = -250.0f; break;
	case 1: TargetY = 0.0f; break;
	case 2: TargetY = 250.0f; break;
	default: TargetY = me->GetActorLocation().Y; break;
	}

	FVector CurrentLocation = me->GetActorLocation();
	FVector TargetLocation = FVector(CurrentLocation.X, TargetY, CurrentLocation.Z);

	if (FVector::Dist2D(CurrentLocation, TargetLocation) < 5.0f)
	{
		me->SetActorLocation(FVector(CurrentLocation.X, TargetY, CurrentLocation.Z));

		mstate = EEnemyState::Rotate;
		if (Anim)
		{
			Anim->AnimState = mstate;
		}
		return;
	}
	
	FVector Dir = (TargetLocation - CurrentLocation).GetSafeNormal();

	me->AddMovementInput(Dir);
}

void UBeastEnemyFSM::RotateState()
{
	if (!me) return;

	if (StartingY > 0.0f)
	{
		TargetYaw = -180.0f;
		
	}
	else if (StartingY < 0.0f)
	{
		TargetYaw = 180.0f;
	}
	else
	{
		TargetYaw = me->GetActorRotation().Yaw;
	}

	FRotator CurrentRotation = me->GetActorRotation();
	FRotator TargetRotation = FRotator(0.0f, TargetYaw, 0.0f);

	if (FMath::IsNearlyEqual(CurrentRotation.Yaw, TargetYaw, 1.0f))
	{
		mstate = EEnemyState::Move;
		if (Anim) Anim->AnimState = mstate;
		return;
	}

	FRotator NewRotation = FMath::RInterpTo(
		CurrentRotation,
		TargetRotation,
		GetWorld()->GetDeltaSeconds(),
		5.0f
	);
	me->SetActorRotation(NewRotation);
}

void UBeastEnemyFSM::OnDamageProcess(int32 damage)
{
	hp -= damage;
	if (hp > 0)
	{
		mstate = EEnemyState::Damage;
		int32 randValue = FMath::RandRange(0, 1);
		FString sectionName = FString::Printf(TEXT("Damage%d"),randValue);
		UGameplayStatics::PlaySound2D(GetWorld(),HitSound);
		me->PlayAnimMontage(Anim->EnemyMontage,1.f,FName(*sectionName));
	}
	else
	{
		mstate = EEnemyState::Die;
		me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		me->CollisionRange->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		me->PlayAnimMontage(Anim->EnemyMontage, 1.f,TEXT("Die"));
		UGameplayStatics::PlaySound2D(GetWorld(), me->ExplosionSound);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), me->ExplosionVFX ,me->GetActorLocation());
	}
	Anim->AnimState = mstate;
}
