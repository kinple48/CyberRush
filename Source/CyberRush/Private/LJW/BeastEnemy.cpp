// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/BeastEnemy.h"

#include "Components/SphereComponent.h"
#include "LJW/BeastEnemyFSM.h"
#include "LJW/FloorTile.h"
#include "Components/BoxComponent.h"
#include "HHS/PlayerMoveComponent.h"
#include "HHS/RunnerPlayerBase.h"
#include "Kismet/GameplayStatics.h"

ABeastEnemy::ABeastEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	FSM = CreateDefaultSubobject<UBeastEnemyFSM>(TEXT("FSM"));
	CollisionRange->SetSphereRadius(80.f);
}

void ABeastEnemy::BeginPlay()
{
	Super::BeginPlay();
	CollisionRange->OnComponentBeginOverlap.AddDynamic(this, &ABeastEnemy::OnCollisionRangeBeginOverlap);
	boxcomp->OnComponentEndOverlap.AddDynamic(this, &ABeastEnemy::OnItemEndOverlap);
}

void ABeastEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABeastEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

void ABeastEnemy::OnCollisionRangeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto player = Cast<ARunnerPlayerBase>(OtherActor);
	if (player)
	{
		player->DamageProcess();
		UGameplayStatics::PlaySound2D(GetWorld(), ExplosionSound);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionVFX, GetActorLocation());
		Destroy();
	}
}

void ABeastEnemy::OnItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (auto Floor = Cast<AFloorTile>(OtherActor))
	{
		//Destroy();
	}
}

void ABeastEnemy::setstartlane(int32 lane)
{
	lanenumber = lane;
}
