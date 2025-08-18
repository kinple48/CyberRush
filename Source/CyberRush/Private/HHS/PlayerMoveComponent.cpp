// Fill out your copyright notice in the Description page of Project Settings.


#include "HHS/PlayerMoveComponent.h"

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
	OwningCharacter->GetCharacterMovement()->MaxWalkSpeed = 800.f;

	UCharacterMovementComponent* MoveComp = OwningCharacter->GetCharacterMovement();
	if (MoveComp)
	{
		MoveComp->MaxWalkSpeed = 800.f;
		MoveComp->JumpZVelocity = 600.f;    // 점프 높이
		MoveComp->AirControl = 0.35f;
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

