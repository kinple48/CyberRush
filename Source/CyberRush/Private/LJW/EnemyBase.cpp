// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/EnemyBase.h"
#include "HHS/PlayerMoveComponent.h"
#include "Components/SphereComponent.h"
#include "HHS/RunnerPlayerBase.h"
#include "LJW/BeastEnemyFSM.h"
#include "Components/BoxComponent.h"
#include "LJW/FloorTile.h"


// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FSM = CreateDefaultSubobject<UBeastEnemyFSM>(TEXT("FSM"));

	CollisionRange = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionRange"));
	CollisionRange->SetupAttachment(RootComponent);

	boxcomp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxcomp"));
	boxcomp->SetupAttachment(RootComponent);
	boxcomp->SetBoxExtent(FVector(1.f,1.f,100.f));
	boxcomp->SetCollisionProfileName(TEXT("ItemChecker"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	CollisionRange->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnCollisionRangeBeginOverlap);
	boxcomp->OnComponentEndOverlap.AddDynamic(this, &AEnemyBase::OnItemEndOverlap);
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
		GetWorld()->GetTimerManager().ClearTimer(player->MoveComp->ScoreTimerHandle);
		Destroy();
	}
}

void AEnemyBase::OnItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (auto Floor = Cast<AFloorTile>(OtherActor))
	{
		Destroy();
	}
}


