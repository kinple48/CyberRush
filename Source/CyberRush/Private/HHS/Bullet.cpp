// Fill out your copyright notice in the Description page of Project Settings.


#include "HHS/Bullet.h"

#include "CyberRushGameMode.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "LJW/BeastEnemy.h"
#include "LJW/BeastEnemyFSM.h"
#include "LJW/DroneEnemy.h"
#include "LJW/DroneEnemyFSM.h"
#include "LJW/EnemyBase.h"
//#include "LJW/EnemyBase.h"
//#include "LJW/EnemyFSM.h"

ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = false;
	
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(15.f);
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	RootComponent = CollisionComp;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetupAttachment(CollisionComp);
	
	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	BulletMovement->InitialSpeed = 4000.f;
	BulletMovement->MaxSpeed = 4000.f;
	BulletMovement->bRotationFollowsVelocity = true;
	BulletMovement->ProjectileGravityScale = 0.f; 

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);
	
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor))
	{
		ACyberRushGameMode* GameMode = Cast<ACyberRushGameMode>(GetWorld()->GetAuthGameMode());

		if (GameMode)
		{
			GameMode->AddScore(ScoreOnHit);
		}
		if (ABeastEnemy* BeastType = Cast<ABeastEnemy>(Enemy))
		{
			UBeastEnemyFSM* enemyFSM = Enemy->FindComponentByClass<UBeastEnemyFSM>();
			if (enemyFSM)
			{
				enemyFSM->OnDamageProcess(1);
			}
		}
		if (ADroneEnemy* DroneType = Cast<ADroneEnemy>(Enemy))
		{
			UDroneEnemyFSM* enemyFSM = Enemy->FindComponentByClass<UDroneEnemyFSM>();
			if (enemyFSM)
			{
				enemyFSM->OnDamageProcess(1);
			}
		}
		SetActive(false);
	}
}

void ABullet::SetActive(bool bValue)
{
	bIsActive = bValue;
	bIsActive = bValue;

	if (BulletMesh)
	{
		BulletMesh->SetVisibility(bValue);
	}

	if (CollisionComp)
	{
		CollisionComp->SetCollisionEnabled(bValue ? ECollisionEnabled::QueryAndPhysics
												  : ECollisionEnabled::NoCollision);
	}

	if (bValue && GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			BulletLifeTimer, this, &ABullet::Deactivate, 1.5f, false);
	}
	else if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(BulletLifeTimer);
	}
}

void ABullet::Deactivate()
{
	SetActive(false);
}