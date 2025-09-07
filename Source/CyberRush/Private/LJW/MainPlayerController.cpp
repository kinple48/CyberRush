// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/MainPlayerController.h"

#include "HHS/PlayerMoveComponent.h"
#include "HHS/RunnerPlayerBase.h"

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindTouch(IE_Pressed, this, &AMainPlayerController::OnTouchBegin);
	InputComponent->BindTouch(IE_Released, this, &AMainPlayerController::OnTouchEnd);
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true; // UI 사용할 거면 마우스 커서 보이게

	FInputModeGameAndUI InputMode;
	SetInputMode(InputMode);
}

void AMainPlayerController::OnTouchBegin(ETouchIndex::Type FingerIndex, FVector Location)
{
	TouchStart = FVector2D(Location.X, Location.Y);
	TouchStartTime = GetWorld()->GetTimeSeconds();
}

void AMainPlayerController::OnTouchEnd(ETouchIndex::Type FingerIndex, FVector Location)
{
	const FVector2D TouchEnd(Location.X, Location.Y);
	const float DeltaX = TouchEnd.X - TouchStart.X;
	const float DeltaTime = GetWorld()->GetTimeSeconds() - TouchStartTime;

	ARunnerPlayerBase* player = Cast<ARunnerPlayerBase>(GetPawn());
	if (!Player) return;

	UPlayerMoveComponent* MoveComp = player->FindComponentByClass<UPlayerMoveComponent>();
	if (!MoveComp) return;

	// 스와이프 판별
	if (FMath::Abs(DeltaX) >= MinSwipeDistance)
	{
		if (DeltaX > 0)
			MoveComp->MoveRight();
		else
			MoveComp->MoveLeft();
	}
	// 탭 (짧고 거의 안 움직인 터치) → 점프
	else if (DeltaTime <= MaxTapDuration)
	{
		MoveComp->Jump();
	}
}


