// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/FloorTileType3.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "HHS/RunnerPlayerBase.h"
//#include "LJW/EnemyBase.h"

AFloorTileType3::AFloorTileType3()
{
	floor->SetRelativeScale3D(FVector(20.0f,10.0f,0.1f));
	floor->SetRelativeLocation(FVector(1000.0f,0.0f,0.0f));

	wall->SetRelativeScale3D(FVector(20.f,0.1f,2.0f));
	wall->SetRelativeLocation(FVector(1000.0f,-500.0f,100.0f));

	wall2->SetRelativeScale3D(FVector(20.f,0.1f,2.0f));
	wall2->SetRelativeLocation(FVector(1000.0f,500.0f,100.0f));
	
	Boxcomp->SetRelativeLocation(FVector(2050.0f,0.0f,200.0f));

	Arrowcomp->SetRelativeLocation(FVector(2000.0f,0.0f,0.0f));
	
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
	
	EnemySponPoint3 = CreateDefaultSubobject<UArrowComponent>(TEXT("EnemySponPoint3"));
	EnemySponPoint3->SetupAttachment(Scenecomp);
	EnemySponPoint3->SetRelativeLocation(FVector(1800.0f,-350.0f,0.0f));
	EnemySponPoint3->SetRelativeRotation(FRotator(0.0f,150.0f,0.0f));
	
	EnemySponPoint4 = CreateDefaultSubobject<UArrowComponent>(TEXT("EnemySponPoint4"));
	EnemySponPoint4->SetupAttachment(Scenecomp);
	EnemySponPoint4->SetRelativeLocation(FVector(1800.0f,350.0f,0.0f));
	EnemySponPoint4->SetRelativeRotation(FRotator(0.0f,210.0f,0.0f));
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
	//GetWorld()->SpawnActor<AEnemyBase>(EnemyFactory, EnemySponPoint1->GetComponentTransform(), SpawnParams);
	//GetWorld()->SpawnActor<AEnemyBase>(EnemyFactory, EnemySponPoint2->GetComponentTransform(), SpawnParams);
	//GetWorld()->SpawnActor<AEnemyBase>(EnemyFactory, EnemySponPoint3->GetComponentTransform(), SpawnParams);
	//GetWorld()->SpawnActor<AEnemyBase>(EnemyFactory, EnemySponPoint4->GetComponentTransform(), SpawnParams);
}
