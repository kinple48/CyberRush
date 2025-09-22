// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/Rocket.h"

#include "Components/SphereComponent.h"
#include "HHS/PlayerMoveComponent.h"
#include "HHS/RunnerPlayerBase.h"
#include "LJW/FloorTile.h"

// Sets default values
ARocket::ARocket()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(15.f);
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	RootComponent = CollisionComp;

	RocketMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RocketMesh"));
	RocketMesh->SetupAttachment(CollisionComp);
}

void ARocket::BeginPlay()
{
	Super::BeginPlay();
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ARocket::OnOverlap);
}

void ARocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!MoveDirection.IsNearlyZero())
	{
		FVector NewLocation = GetActorLocation() + MoveDirection * Speed * DeltaTime;
		SetActorLocation(NewLocation);
	}
}

void ARocket::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ARunnerPlayerBase* player = Cast<ARunnerPlayerBase>(OtherActor))
	{
		player->bIsDead = true;
		GetWorld()->GetTimerManager().ClearTimer(player->MoveComp->ScoreTimerHandle);
		Destroy();
	}
	else if (AFloorTile* floor = Cast<AFloorTile>(OtherActor))
	{
		Destroy();
	}
}

void ARocket::Init(FVector InDirection)
{
	MoveDirection = InDirection;
}

