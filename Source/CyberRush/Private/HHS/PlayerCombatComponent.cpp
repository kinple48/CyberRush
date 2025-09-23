// Fill out your copyright notice in the Description page of Project Settings.


#include "HHS/PlayerCombatComponent.h"

#include "EnhancedInputComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "HHS/Bullet.h"
#include "HHS/PlayerAnimInstance.h"
#include "HHS/PlayerMoveComponent.h"
#include "HHS/RunnerPlayerBase.h"
#include "Kismet/GameplayStatics.h"

UPlayerCombatComponent::UPlayerCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	FirePositionComp = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePositionComp"));

}


void UPlayerCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<ARunnerPlayerBase>(GetOwner());
	Anim = Cast<UPlayerAnimInstance>(Player->GetMesh()->GetAnimInstance());
	if (Player)
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

	MagazineAmmo = maxMagazineAmmo;
	ReserveAmmo = maxReserveAmmo;
}

void UPlayerCombatComponent::SetupInputBinding(UEnhancedInputComponent* InputComponent)
{
	InputComponent->BindAction(IA_Fire, ETriggerEvent::Started, this, &UPlayerCombatComponent::Fire);
}

void UPlayerCombatComponent::Fire()
{
	if (!bCanFire || Player->bIsDead || IsReloading) return;
	bCanFire = false;
	GetWorld()->GetTimerManager().SetTimer(
		FireCooldownTimer,
		[this]()
		{
			bCanFire = true;
		},
		FireRate,
		false
	);
	
	if (Player->MoveComp->bCanRun && !isMoving)
	{
		Anim->isAttack = true;
		GetWorld()->GetTimerManager().ClearTimer(AttackStateResetTimer);
		GetWorld()->GetTimerManager().SetTimer(
			AttackStateResetTimer,
			this,
			&UPlayerCombatComponent::ResetAttack,
			AttackResetTime,
			false
		);
		if (MagazineAmmo > 0)
		{
			UGameplayStatics::PlaySound2D(GetWorld(),FireSound);
			MakeBullet();
			MagazineAmmo--;
		}
		else
		{
			if (ReserveAmmo > 0)
			{
				if (!IsReloading)
				{
					UGameplayStatics::PlaySound2D(GetWorld(),ReloadSound);
				}
				IsReloading = true;
				Anim->isReloading = true;
			}
			else
			{
				UGameplayStatics::PlaySound2D(GetWorld(),EmptySound);
			}
		}
	}
}

void UPlayerCombatComponent::MakeBullet()
{
	bool FindResult = false;
	FTransform t = FirePositionComp->GetComponentTransform();

	for( int i = 0; i < Magazine.Num(); ++i )
	{
		UE_LOG(LogTemp, Warning, TEXT("Bullet #%d"), i);
		
		if (Magazine[i] && Magazine[i]->bIsActive == false)

		{
			FindResult = true;

			Magazine[i]->SetActive(true);
			Magazine[i]->SetActorLocationAndRotation(t.GetLocation(), t.GetRotation());

			break;
		}
	}
}

void UPlayerCombatComponent::ResetAttack()
{
	if (Anim)
	{
		Anim->isAttack = false;
	}
}

void UPlayerCombatComponent::ReloadGun()
{
	int32 AmmoNeeded = maxMagazineAmmo - MagazineAmmo;

	int32 AmmoToReload = FMath::Min(AmmoNeeded, ReserveAmmo);

		
	if (AmmoNeeded <= 0 || ReserveAmmo <= 0 || AmmoToReload <= 0)
	{
		return;
	}
		
	MagazineAmmo += AmmoToReload;
	ReserveAmmo -= AmmoToReload;
	IsReloading = false;
}


