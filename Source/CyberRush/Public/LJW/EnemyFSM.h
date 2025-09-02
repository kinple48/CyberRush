// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"

UENUM()
enum class EEnemyState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Move UMETA(DisplayName = "Move"),
	Damage UMETA(DisplayName = "Damage"),
	Die UMETA(DisplayName = "Die"),
	
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CYBERRUSH_API UEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	EEnemyState mState = EEnemyState::Idle;

	UPROPERTY()
	class ARunnerPlayerBase* target;

	UPROPERTY()
	class AEnemyBase* me;

	float IdleDelayTime = 0.3f;
	float CurrentTime = 0.0f;
	
	UPROPERTY(EditAnywhere, Category = FSM)
	float damageDelayTime = 1.f;
	
	void IdleState();
	void MoveState();
	void DamageState();
	void DieState();

	void OnDamageProcess(int32 Damage);

	int32 hp = 2;

	UPROPERTY()
	class UEnemyAnim* Anim;
};
