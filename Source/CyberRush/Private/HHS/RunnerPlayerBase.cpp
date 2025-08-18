 // Fill out your copyright notice in the Description page of Project Settings.


#include "HHS/RunnerPlayerBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HHS/PlayerMoveComponent.h"

 ARunnerPlayerBase::ARunnerPlayerBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'"));

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

	if(MoveComp)
	{
		if(UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			MoveComp->SetupInputBinding(EnhancedInput);
		}
	}
}

