// Fill out your copyright notice in the Description page of Project Settings.


#include "HHS/PlayerMoveComponent.h"

#include "EnhancedInputComponent.h"
#include "HHS/RunnerPlayerBase.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UPlayerMoveComponent::UPlayerMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UPlayerMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

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


// Called every frame
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

	// 쪼그리기 시작
	OwningCharacter->Crouch();
}

void UPlayerMoveComponent::SlideEnd()
{
	if(!OwningCharacter) return;

	// 원래 키 높이로 돌아가기
	OwningCharacter->UnCrouch();
}

void UPlayerMoveComponent::SetupInputBinding(UEnhancedInputComponent* InputComponent)
{
	InputComponent->BindAction(IA_MoveLeft, ETriggerEvent::Started, this, &UPlayerMoveComponent::MoveLeft);
	InputComponent->BindAction(IA_MoveRight, ETriggerEvent::Started, this, &UPlayerMoveComponent::MoveRight);
	InputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &UPlayerMoveComponent::Jump);
	InputComponent->BindAction(IA_Slide, ETriggerEvent::Started, this, &UPlayerMoveComponent::SlideStart);
	InputComponent->BindAction(IA_Slide, ETriggerEvent::Completed, this, &UPlayerMoveComponent::SlideEnd);

}

