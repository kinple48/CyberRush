// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/FloorTileType3.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "HHS/RunnerPlayerBase.h"
#include "LJW/BeastEnemy.h"
//#include "LJW/EnemyBase.h"

AFloorTileType3::AFloorTileType3()
{
	EnemySensor = CreateDefaultSubobject<UBoxComponent>(TEXT("EnemySensor"));
	EnemySensor->SetRelativeLocation(FVector(-50.0f,0.0f,200.0f));
	EnemySensor->SetBoxExtent(FVector(32.0f,500.0f,200.0f));
	EnemySensor->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	EnemySensor->SetupAttachment(Scenecomp);

	EnemySponPoint1 = CreateDefaultSubobject<UArrowComponent>(TEXT("EnemySponPoint1"));
	EnemySponPoint1->SetupAttachment(Scenecomp);
	EnemySponPoint1->SetRelativeLocation(FVector(1400.0f,-350.0f,0.0f));
	EnemySponPoint1->SetRelativeRotation(FRotator(0.0f,150.0f,0.0f));

	EnemySponPoint2 = CreateDefaultSubobject<UArrowComponent>(TEXT("EnemySponPoint2"));
	EnemySponPoint2->SetupAttachment(Scenecomp);
	EnemySponPoint2->SetRelativeLocation(FVector(1400.0f,350.0f,0.0f));
	EnemySponPoint2->SetRelativeRotation(FRotator(0.0f,210.0f,0.0f));
}

void AFloorTileType3::BeginPlay()
{
	Super::BeginPlay();
	EnemySensor->OnComponentBeginOverlap.AddDynamic(this, &AFloorTileType3::OnSensorBeginOverlap);	
}

void AFloorTileType3::OnSensorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto Player = Cast<ARunnerPlayerBase>(OtherActor))
	{
		SpawnEnemy();
	}
}

void AFloorTileType3::SpawnEnemy()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	GetWorld()->SpawnActor<AEnemyBase>(EnemyFactory, EnemySponPoint1->GetComponentTransform(), SpawnParams);
	GetWorld()->SpawnActor<AEnemyBase>(EnemyFactory, EnemySponPoint2->GetComponentTransform(), SpawnParams);
}
