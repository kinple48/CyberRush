// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"
#include "DroneEnemyFSM.generated.h"
UENUM()
enum class EDroneState : uint8
{
	Idle,
	Move,
	Damage,
	Attack,
	Die
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CYBERRUSH_API UDroneEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDroneEnemyFSM();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	EDroneState mstate = EDroneState::Idle;

	UPROPERTY()
	class ADroneEnemy* Me;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = FSM)
	class ARunnerPlayerBase* target;
	
	void IdleState();
	void MoveState();
	void AttackState();
	void DieState();

	float AttackLocY;
	void OnDamageProcess(int32 damage);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSM)
	int32 hp = 4;
	
	float AttackDelayTime = 3.0f;
	float ElapsedTimeInMove = 0.0f;

	void SetReticleVisible(bool bVisible);
	float GetNearestLaneY(float PlayerY);

	bool bHasFiredRocket = false;
	float ElapsedAttackTime = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	TSubclassOf<class ARocket> RocketFactory;

	void FireRocket();
};
