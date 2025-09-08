// Fill out your copyright notice in the Description page of Project Settings.


#include "HHS/PlayerMoveComponent.h"

#include "CyberRushGameMode.h"
#include "EnhancedInputComponent.h"
#include "HHS/RunnerPlayerBase.h"

#include "GameFramework/CharacterMovementComponent.h"

UPlayerMoveComponent::UPlayerMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	
}


void UPlayerMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningCharacter = Cast<ARunnerPlayerBase>(GetOwner());

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
			true);
	}
}


void UPlayerMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 앞으로 자동 달리기
	if (OwningCharacter)
	{
		OwningCharacter->AddMovementInput(OwningCharacter->GetActorForwardVector(), 1.0f);
	}
	
	UpdateLanePosition(DeltaTime);

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
	CurrentLane = FMath::Clamp(CurrentLane - 1, 0, 2);
	UE_LOG(LogTemp, Warning, TEXT("CurrentLane: %d"), CurrentLane);

}

void UPlayerMoveComponent::MoveRight()
{
	CurrentLane = FMath::Clamp(CurrentLane + 1, 0, 2);
	UE_LOG(LogTemp, Warning, TEXT("CurrentLane: %d"), CurrentLane);

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

	// 이미 점프 중이 아닐 때만 점프
	if (!OwningCharacter->GetCharacterMovement()->IsFalling())
	{
		OwningCharacter->Jump();
		UE_LOG(LogTemp, Warning, TEXT("Jump"));

	}
}

void UPlayerMoveComponent::SlideStart()
{
	if(!OwningCharacter) return;

	OwningCharacter->Crouch();
}

void UPlayerMoveComponent::SlideEnd()
{
	if(!OwningCharacter) return;

	OwningCharacter->UnCrouch();
}

void UPlayerMoveComponent::SetupInputBinding(UEnhancedInputComponent* InputComponent)
{
	InputComponent->BindAction(IA_MoveLeft, ETriggerEvent::Started, this, &UPlayerMoveComponent::MoveLeft);
	InputComponent->BindAction(IA_MoveRight, ETriggerEvent::Started, this, &UPlayerMoveComponent::MoveRight);
	InputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &UPlayerMoveComponent::Jump);
	//InputComponent->BindAction(IA_Slide, ETriggerEvent::Started, this, &UPlayerMoveComponent::SlideStart);
	//InputComponent->BindAction(IA_Slide, ETriggerEvent::Completed, this, &UPlayerMoveComponent::SlideEnd);
	

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

