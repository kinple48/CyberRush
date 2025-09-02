 // Fill out your copyright notice in the Description page of Project Settings.


#include "HHS/RunnerPlayerBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HHS/PlayerCombatComponent.h"
#include "HHS/PlayerMoveComponent.h"

 ARunnerPlayerBase::ARunnerPlayerBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/IdaFaber/Meshes/Girl/SK_CYBER_SF_F_01.SK_CYBER_SF_F_01'"));

	if (TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);

		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f ));
	}

	RunnerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("RunnerCam"));
	RunnerCam->SetupAttachment(RootComponent);
	RunnerCam->SetRelativeLocation(FVector(-300.f, 0.f, 300.f));
	RunnerCam->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));
	
	MoveComp = CreateDefaultSubobject<UPlayerMoveComponent>(TEXT("MoveComp"));
 	CombatComp = CreateDefaultSubobject<UPlayerCombatComponent>(TEXT("CombatComp"));


 	GunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMeshComp"));
	GunMeshComp->SetupAttachment(GetMesh(), TEXT("ik_hand_rSocket"));
 	ConstructorHelpers::FObjectFinder<USkeletalMesh> TmpGun(TEXT("/Script/Engine.SkeletalMesh'/Game/Scifi_Arsenal_Vol2/Skeletal_Meshes/Sci-fi_Pistol_01/SK_Sci-fi_Pistol_01_NoIronsight.SK_Sci-fi_Pistol_01_NoIronsight'"));
 	if (TmpGun.Succeeded())
 	{
 		GunMeshComp->SetSkeletalMesh(TmpGun.Object);
 		GunMeshComp->SetRelativeLocationAndRotation(FVector(-6.705495f, -0.403527f, 2.557798f), FRotator(0.625342f, -38.782035f, 187.405683f));
	}
 	
	//ConstructorHelpers::FClassFinder<UTPSPlayerAnimInstance> TempAnimInst(TEXT("/Script/Engine.AnimBlueprint'/Game/NYS/Blueprints/Anim/ABP_TPSPlayer.ABP_TPSPlayer_C'"));
//
	//if( TempAnimInst.Succeeded() )
	//{
	//	GetMesh()->SetAnimInstanceClass(TempAnimInst.Class);
	//}

	// 자동 전방 이동
	GetCharacterMovement()->MaxWalkSpeed = 50.f;
	GetCharacterMovement()->bOrientRotationToMovement = false; // 플레이어 회전 없이 이동
	bUseControllerRotationYaw = false;

}

void ARunnerPlayerBase::BeginPlay()
{
	Super::BeginPlay();

 	auto pc = Cast<APlayerController>(Controller);
 	if( pc )
 	{
 		auto subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());

 		if( subsystem )
 		{
 			subsystem->AddMappingContext(IMC_CR, 0);
 		}
 	}	
}

void ARunnerPlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARunnerPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

 	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
 	{
 		if (MoveComp)
 		{
 			MoveComp->SetupInputBinding(EnhancedInput);
 		}
 		if (CombatComp)
 		{
 			CombatComp->SetupInputBinding(EnhancedInput);
 		}
 	}
}

void ARunnerPlayerBase::DamageProcess()
{
 	bIsDead = true;
}