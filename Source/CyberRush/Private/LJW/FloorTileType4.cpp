// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/FloorTileType4.h"

#include "EngineUtils.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "HHS/RunnerPlayerBase.h"
#include "LJW/DroneEnemy.h"
#include "LJW/EnemyBase.h"

AFloorTileType4::AFloorTileType4()
{
	EnemySensor = CreateDefaultSubobject<UBoxComponent>(TEXT("EnemySensor"));
	EnemySensor->SetRelativeLocation(FVector(-50.0f,0.0f,200.0f));
	EnemySensor->SetBoxExtent(FVector(32.0f,500.0f,200.0f));
	EnemySensor->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	EnemySensor->SetupAttachment(Scenecomp);

	EnemySponPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("EnemySponPoint"));
	EnemySponPoint->SetupAttachment(Scenecomp);
	EnemySponPoint->SetRelativeLocation(FVector(1400.0f,0.0f,1000.0f));
	EnemySponPoint->SetRelativeRotation(FRotator(0.0f,0.0f,0.0f));

}

void AFloorTileType4::BeginPlay()
{
	Super::BeginPlay();
	EnemySensor->OnComponentBeginOverlap.AddDynamic(this, &AFloorTileType4::OnSensorBeginOverlap);
}

void AFloorTileType4::OnSensorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto Player = Cast<ARunnerPlayerBase>(OtherActor))
	{
		SpawnEnemy();
	}
}

void AFloorTileType4::SpawnEnemy()
{
	for (TActorIterator<ADroneEnemy> It(GetWorld()); It; ++It)
	{
		if (IsValid(*It) && !It->IsPendingKillPending())
		{
			return;
		}
	}
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	GetWorld()->SpawnActor<AEnemyBase>(EnemyFactory, EnemySponPoint->GetComponentTransform(), SpawnParams);
}
