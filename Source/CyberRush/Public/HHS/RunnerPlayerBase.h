// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RunnerPlayerBase.generated.h"

UCLASS()
class CYBERRUSH_API ARunnerPlayerBase : public ACharacter
{
	GENERATED_BODY()

public:
	ARunnerPlayerBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* RunnerCam;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* IMC_CR;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPlayerMoveComponent* MoveComp;

	// ========== anim ==========
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Anim")
	float ForwardSpeed;

};
