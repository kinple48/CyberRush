// Fill out your copyright notice in the Description page of Project Settings.


#include "HHS/PlayerMoveComponent.h"

#include "CyberRushGameMode.h"
#include "EnhancedInputComponent.h"
#include "HHS/RunnerPlayerBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "HHS/PlayerAnimInstance.h"
#include "Kismet/GameplayStatics.h"

UPlayerMoveComponent::UPlayerMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	
}


void UPlayerMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningCharacter = Cast<ARunnerPlayerBase>(GetOwner());
	Anim = Cast<UPlayerAnimInstance>(OwningCharacter->GetMesh()->GetAnimInstance());

	// 이동속도 조절
	OwningCharacter->GetCharacterMovement()->MaxWalkSpeed = 1500.f;

	UCharacterMovementComponent* MoveComp = OwningCharacter->GetCharacterMovement();
	if (MoveComp)
	{
		MoveComp->MaxWalkSpeed = 1500.f;
		MoveComp->JumpZVelocity = 1150.f;
		MoveComp->AirControl = 1.f;
	}

	GameModeRef = Cast<ACyberRushGameMode>(GetWorld()->GetAuthGameMode());
	
	if (GameModeRef)
	{
		GetWorld()->GetTimerManager().SetTimer(
			ScoreTimerHandle, 
			this, 
			&UPlayerMoveComponent::AddScoreOverTime, 
			ScoreInterval, 
			true, 3.5f);
	}

}


void UPlayerMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 앞으로 자동 달리기
	if (OwningCharacter && !OwningCharacter->bIsDead && bCanRun)
	{
		OwningCharacter->AddMovementInput(OwningCharacter->GetActorForwardVector(), 1.0f);
		UpdateLanePosition(DeltaTime);
	}

	UCharacterMovementComponent* MoveComp = OwningCharacter->GetCharacterMovement();
	if (MoveComp->IsFalling())
	{
		const float VelocityZ = MoveComp->Velocity.Z;

		if (VelocityZ > 0.f)
		{
			MoveComp->GravityScale = 3.0f;
		}
		else
		{
			MoveComp->GravityScale = 5.0f;
		}
	}
	else
	{
		MoveComp->GravityScale = 3.0f;
	}
}

void UPlayerMoveComponent::MoveLeft()
{
	if (bCanChangeLane&&!OwningCharacter->GetCharacterMovement()->IsFalling() && bCanRun && CurrentLane !=0)
	{
		bCanChangeLane = false;
		GetWorld()->GetTimerManager().SetTimer(LaneCooldownHandle, this, &UPlayerMoveComponent::ResetLaneCooldown, LaneChangeCooldown, false);
		CurrentLane = FMath::Clamp(CurrentLane - 1, 0, 2);
		OwningCharacter->PlayAnimMontage(Anim->PlayerMontage, 1.f,TEXT("Left"));
	}
}

void UPlayerMoveComponent::MoveRight()
{
	if (bCanChangeLane&&!OwningCharacter->GetCharacterMovement()->IsFalling() && bCanRun && CurrentLane !=2)
	{
		bCanChangeLane = false;
		GetWorld()->GetTimerManager().SetTimer(LaneCooldownHandle, this, &UPlayerMoveComponent::ResetLaneCooldown, LaneChangeCooldown, false);
		CurrentLane = FMath::Clamp(CurrentLane + 1, 0, 2);
		OwningCharacter->PlayAnimMontage(Anim->PlayerMontage, 1.f,TEXT("Right"));
	}
}

void UPlayerMoveComponent::UpdateLanePosition(float DeltaTime)
{
	if (!OwningCharacter) return;
	
	FVector CurrentLocation = OwningCharacter->GetActorLocation();
	float TargetY = (CurrentLane - 1) * LaneDistance;
	CurrentLocation.Y = FMath::FInterpTo(CurrentLocation.Y, TargetY, DeltaTime, LaneInterpSpeed);
	OwningCharacter->SetActorLocation(CurrentLocation);
	
}

void UPlayerMoveComponent::Jump()
{
	if (!OwningCharacter) return;

	if (!OwningCharacter->GetCharacterMovement()->IsFalling() && !OwningCharacter->bIsDead && bCanRun)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), JumpSound);
		OwningCharacter->Jump();
	}
}

void UPlayerMoveComponent::SetupInputBinding(UEnhancedInputComponent* InputComponent)
{
	InputComponent->BindAction(IA_MoveLeft, ETriggerEvent::Started, this, &UPlayerMoveComponent::MoveLeft);
	InputComponent->BindAction(IA_MoveRight, ETriggerEvent::Started, this, &UPlayerMoveComponent::MoveRight);
	InputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &UPlayerMoveComponent::Jump);
}

void UPlayerMoveComponent::AddScoreOverTime()
{
	if (GameModeRef && OwningCharacter && !OwningCharacter->bIsDead)
	{
		GameModeRef->AddScore(ScorePerInterval);
	}
	
	else if(OwningCharacter && OwningCharacter->bIsDead)
	{
		GetWorld()->GetTimerManager().ClearTimer(ScoreTimerHandle);
	}
}

void UPlayerMoveComponent::ResetLaneCooldown()
{
	bCanChangeLane = true;
}

