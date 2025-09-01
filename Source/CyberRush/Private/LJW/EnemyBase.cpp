// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/EnemyBase.h"

#include "Components/SphereComponent.h"
#include "HHS/RunnerPlayerBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;
	AttackRange = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRange"));
	AttackRange->SetSphereRadius(100.f);
	AttackRange->SetupAttachment(GetRootComponent());
	SkeletalMesh = CreateDefaultSubobject<USkeletalMesh>(TEXT("SkeletalMesh"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	AttackRange->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnAttackRangeBeginOverlap);
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBase::OnAttackRangeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto player = Cast<ARunnerPlayerBase>(OtherActor))
	{
		const FVector EmitterScale(2.0f);
		UGameplayStatics::PlaySound2D(GetWorld(),ExplosionSound);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ExplosionVFX,GetActorLocation(), FRotator::ZeroRotator, EmitterScale, true);
		Destroy();
	}
}

