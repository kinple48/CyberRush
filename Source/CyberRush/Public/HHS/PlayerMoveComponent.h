// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RunnerPlayerBase.h"
#include "Components/ActorComponent.h"
#include "EnhancedInputComponent.h"
#include "PlayerMoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CYBERRUSH_API UPlayerMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerMoveComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ========== 레인 이동 ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Runner|Movement")
	int32 CurrentLane = 1; // 0: Left, 1: Center, 2: Right

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Runner|Movement")
	float LaneDistance = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Runner|Movement")
	float LaneInterpSpeed = 10.f;

	void MoveLeft();
	void MoveRight();
	void UpdateLanePosition(float DeltaTime);

	void Jump();

	void SlideStart();
	void SlideEnd();
	
private:
	UPROPERTY()
	ARunnerPlayerBase* OwningCharacter;
	
public:
	void SetupInputBinding(UEnhancedInputComponent* InputComponent);
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_MoveLeft;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_MoveRight;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_Jump;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_Slide;
	
	UPROPERTY()
	class ACyberRushGameMode* GameModeRef;
	
	FTimerHandle ScoreTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Runner|Score")
	float ScoreInterval = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Runner|Score")
	int32 ScorePerInterval = 5;

	void AddScoreOverTime();

	UPROPERTY(EditAnywhere, Category="Jump Settings")
	float GravityScale_Up = 0.5f;

	UPROPERTY(EditAnywhere, Category="Jump Settings")
	float GravityScale_Down = 2.5f;
};
