#include "LJW/DroneEnemyFSM.h"

#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "HHS/RunnerPlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "LJW/DroneEnemy.h"
#include "LJW/Rocket.h"

UDroneEnemyFSM::UDroneEnemyFSM()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UDroneEnemyFSM::BeginPlay()
{
	Super::BeginPlay();
	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), ARunnerPlayerBase::StaticClass());
	if (actor)
	{
		target = Cast<ARunnerPlayerBase>(actor);
	}
	
	Me = Cast<ADroneEnemy>(GetOwner());
}

void UDroneEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString logMsg = UEnum::GetValueAsString(mstate);
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Red, logMsg);
	
	switch (mstate)
	{
	case EDroneState::Idle:
		IdleState();
		break;
	case EDroneState::Move:
		MoveState();
		break;
	case EDroneState::Attack:
		AttackState();
		break;
	case EDroneState::Die:
		DieState();
		break;
	}
}

void UDroneEnemyFSM::IdleState()
{
	if (!target) return;
	SetReticleVisible(false);
	FVector Current = Me->GetActorLocation();

	const float ForwardOffset = 2500.f;
	float TargetX = target->GetActorLocation().X + ForwardOffset;
	float TargetY = Current.Y;
	float TargetZ = 370.f;
	FVector Target(TargetX, TargetY, TargetZ);
	FVector NewLoc = FMath::VInterpTo(Current, Target, GetWorld()->GetDeltaSeconds(), 3.0f);
	Me->SetActorLocation(NewLoc);
	if (FMath::IsNearlyEqual(NewLoc.Z, 370.f, 1.0f))
	{
		mstate = EDroneState::Move;
	}
}

void UDroneEnemyFSM::MoveState()
{
	if (!target || !Me) return;
	SetReticleVisible(true);
	FVector CurrentLoc = Me->GetActorLocation();
	FVector PlayerLoc = target->GetActorLocation();

	const float ForwardOffset = 2500.f;
	float TargetX = PlayerLoc.X + ForwardOffset;
	float TargetY = PlayerLoc.Y;
	float TargetZ = 370.f;

	FVector TargetLoc(TargetX, TargetY, TargetZ);
	FVector NewLoc = FMath::VInterpTo(CurrentLoc, TargetLoc, GetWorld()->GetDeltaSeconds(), 2.0f);

	Me->SetActorLocation(NewLoc);
	
	ElapsedTimeInMove += GetWorld()->GetDeltaSeconds();

	if (ElapsedTimeInMove >= AttackDelayTime)
	{
		AttackLocY = GetNearestLaneY(PlayerLoc.Y);
		bHasFiredRocket =true;
		mstate = EDroneState::Attack;
		ElapsedTimeInMove = 0.0f;
	}
}

void UDroneEnemyFSM::AttackState()
{
	if (!target || !Me || !RocketFactory || target->bIsDead) return;
	SetReticleVisible(true);
	FVector CurrentLoc = Me->GetActorLocation();
	FVector PlayerLoc = target->GetActorLocation();

	const float ForwardOffset = 2500.f;
	float TargetX = PlayerLoc.X + ForwardOffset;
	float TargetZ = 370.f;

	FVector TargetLoc(TargetX, AttackLocY, TargetZ);
	FVector NewLoc = FMath::VInterpTo(CurrentLoc, TargetLoc, GetWorld()->GetDeltaSeconds(), 2.0f);
	Me->SetActorLocation(NewLoc);
	
	ElapsedAttackTime += GetWorld()->GetDeltaSeconds();

	if (bHasFiredRocket && ElapsedAttackTime >= 0.5f)
	{
		FVector FireStart = Me->GetActorLocation();

		ADroneEnemy* Drone = Cast<ADroneEnemy>(Me);
		if (!Drone || !Drone->ReticleDecal) return;

		FVector FireTarget = Drone->ReticleDecal->GetComponentLocation();

		FVector FireDirection = (FireTarget - FireStart).GetSafeNormal();
		FRotator FireRotation = FireDirection.Rotation();

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ARocket* Rocket = GetWorld()->SpawnActor<ARocket>(RocketFactory, FireStart, FireRotation, SpawnParams);
		UGameplayStatics::PlaySound2D(GetWorld(), Me->FireSound);
		if (Rocket)
		{
			Rocket->Init(FireDirection);
		}
		bHasFiredRocket = false;
	}
	
	if (ElapsedAttackTime >= 1.5f)
	{
		mstate = EDroneState::Move;
		ElapsedAttackTime = 0.0f;
	}
}

void UDroneEnemyFSM::DieState()
{
	Me->Destroy();
}

void UDroneEnemyFSM::OnDamageProcess(int32 damage)
{
	if (hp <= 0)
	{
		mstate = EDroneState::Die;
	}
	else
	{
		hp -= damage;
		UGameplayStatics::PlaySound2D(GetWorld(),HitSound);
	}
}

void UDroneEnemyFSM::SetReticleVisible(bool bVisible)
{
	if (ADroneEnemy* Drone = Cast<ADroneEnemy>(Me))
	{
		if (Drone->ReticleDecal)
		{
			Drone->ReticleDecal->SetVisibility(bVisible);
		}
	}
}

float UDroneEnemyFSM::GetNearestLaneY(float PlayerY)
{
	TArray<float> LaneYs = { -250.f, 0.f, 250.f };

	float ClosestY = LaneYs[0];
	float MinDistance = FMath::Abs(PlayerY - LaneYs[0]);

	for (int32 i = 1; i < LaneYs.Num(); ++i)
	{
		float Dist = FMath::Abs(PlayerY - LaneYs[i]);
		if (Dist < MinDistance)
		{
			MinDistance = Dist;
			ClosestY = LaneYs[i];
		}
	}
	return ClosestY;
}