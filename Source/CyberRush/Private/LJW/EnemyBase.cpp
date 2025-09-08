// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/EnemyBase.h"

#include "Components/SphereComponent.h"
#include "HHS/RunnerPlayerBase.h"
#include "LJW/BeastEnemyFSM.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FSM = CreateDefaultSubobject<UBeastEnemyFSM>(TEXT("FSM"));

	CollisionRange = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionRange"));
	CollisionRange->SetupAttachment(RootComponent);
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	CollisionRange->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnCollisionRangeBeginOverlap);
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBase::OnCollisionRangeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto player = Cast<ARunnerPlayerBase>(OtherActor);
	if (player)
	{
		player->bIsDead = true;
		Destroy();
	}
}


