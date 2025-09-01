// Fill out your copyright notice in the Description page of Project Settings.


#include "HHS/PlayerCombatComponent.h"

#include "EnhancedInputComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "HHS/Bullet.h"
#include "HHS/RunnerPlayerBase.h"

UPlayerCombatComponent::UPlayerCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	FirePositionComp = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePositionComp"));

}


void UPlayerCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (ARunnerPlayerBase* Player = Cast<ARunnerPlayerBase>(GetOwner()))
	{
		if (Player->GunMeshComp)
		{
			// 소켓에 붙이기
			FirePositionComp->AttachToComponent(Player->GunMeshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("MuzzleSocket"));
		}
	}
	
	for( int32 i = 0; i < MaxBulletCount; ++i )
	{
		FActorSpawnParameters params;
		// 항상 스폰되게 한다.
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ABullet* bullet = GetWorld()->SpawnActor<ABullet>(BulletClass, params);
		bullet->SetActive(false);
		Magazine.Add(bullet);
	}
}

void UPlayerCombatComponent::SetupInputBinding(UEnhancedInputComponent* InputComponent)
{
	InputComponent->BindAction(IA_Fire, ETriggerEvent::Started, this, &UPlayerCombatComponent::Fire);
}

void UPlayerCombatComponent::Fire()
{
	//if (ARunnerPlayerBase* Player = Cast<ARunnerPlayerBase>(GetOwner()))
	//{
	//	FVector SpawnLoc = Player->GetActorLocation() + Player->GetActorForwardVector() * MuzzleOffset.X + FVector(0,0,MuzzleOffset.Z);
	//	FRotator SpawnRot = Player->GetActorRotation();
//
	//	FActorSpawnParameters SpawnParams;
	//	SpawnParams.Owner = Player;
//
	//	GetWorld()->SpawnActor<ABullet>(BulletClass, SpawnLoc, SpawnRot, SpawnParams);
	//}
	MakeBullet();
}

void UPlayerCombatComponent::MakeBullet()
{
	bool FindResult = false;
	FTransform t = FirePositionComp->GetComponentTransform();

	for( int i = 0; i < Magazine.Num(); ++i )
	{
		UE_LOG(LogTemp, Warning, TEXT("Bullet #%d"), i);
		
		if (Magazine[i]->bIsActive == false)

		{
			FindResult = true;

			Magazine[i]->SetActive(true);
			Magazine[i]->SetActorLocationAndRotation(t.GetLocation(), t.GetRotation());

			break;
		}
	}

	if( FindResult == false )
	{
		UE_LOG(LogTemp, Warning, TEXT("활성화된 총알 없음"));
	}
}
