#include "LJW/MainPlayerController.h"

#include "HHS/PlayerCombatComponent.h"
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
	bShowMouseCursor = true;

	FInputModeGameAndUI InputMode;
	SetInputMode(InputMode);
}

void AMainPlayerController::OnTouchBegin(ETouchIndex::Type FingerIndex, FVector Location)
{
	TouchStart = FVector2D(Location.X, Location.Y);
	TouchStartTime = GetWorld()->GetTimeSeconds();
}

/*
void AMainPlayerController::OnTouchEnd(ETouchIndex::Type FingerIndex, FVector Location)
{
	const FVector2D TouchEnd(Location.X, Location.Y);
	const float DeltaX = TouchEnd.X - TouchStart.X;
	const float DeltaY = TouchStart.Y - TouchEnd.Y; // ↑ 방향이 양수
	const float DeltaTime = GetWorld()->GetTimeSeconds() - TouchStartTime;

	ARunnerPlayerBase* me = Cast<ARunnerPlayerBase>(GetPawn());
	if (!me) return;

	UPlayerMoveComponent* MoveComp = me->FindComponentByClass<UPlayerMoveComponent>();
	if (!MoveComp) return;

	// 주 방향 결정
	if (FMath::Abs(DeltaX) > FMath::Abs(DeltaY))
	{
		// 좌우 스와이프
		if (FMath::Abs(DeltaX) >= MinSwipeDistance)
		{
			if (DeltaX > 0)
				MoveComp->MoveRight();
			else
				MoveComp->MoveLeft();
		}
	}
	else
	{
		if (DeltaY >= MinSwipeDistance)
		{
			MoveComp->Jump();
		}
	}
}
*/

void AMainPlayerController::OnTouchEnd(ETouchIndex::Type FingerIndex, FVector Location)
{
	const FVector2D TouchEnd(Location.X, Location.Y);
	const float DeltaX = TouchEnd.X - TouchStart.X;
	const float DeltaY = TouchStart.Y - TouchEnd.Y; // ↑ 방향이 양수
	const float DeltaTime = GetWorld()->GetTimeSeconds() - TouchStartTime;

	ARunnerPlayerBase* me = Cast<ARunnerPlayerBase>(GetPawn());
	if (!me) return;

	UPlayerMoveComponent* MoveComp = me->FindComponentByClass<UPlayerMoveComponent>();
	UPlayerCombatComponent* CombatComp = me->FindComponentByClass<UPlayerCombatComponent>();

	if (!MoveComp || !CombatComp) return;

	// 1. 주 방향 판별
	if (FMath::Abs(DeltaX) > FMath::Abs(DeltaY))
	{
		if (FMath::Abs(DeltaX) >= MinSwipeDistance)
		{
			if (DeltaX > 0)
				MoveComp->MoveRight();
			else
				MoveComp->MoveLeft();
			return;
		}
	}
	else
	{
		if (DeltaY >= MinSwipeDistance)
		{
			MoveComp->Jump();
			return;
		}
	}

	// 2. 스와이프도 아니고, 짧은 탭이면 Fire 실행
	if (DeltaTime <= MaxTapDuration &&
		FVector2D::Distance(TouchStart, TouchEnd) < MinSwipeDistance)
	{
		CombatComp->Fire();
	}
}
