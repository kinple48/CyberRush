#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BeastEnemyFSM.generated.h"
UENUM()
enum class EEnemyState : uint8
{
	Idle,
	Move,
	Damage,
	Die
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CYBERRUSH_API UBeastEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBeastEnemyFSM();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	EEnemyState mstate = EEnemyState::Idle;

	void IdleState();
	void MoveState();
	void DamageState();
	void DieState();

	float IdleDelayTime = 0.5f;
	float CurrentTime = 0.f;
	float damageDelayTime = 0.5f;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = FSM)
	class ARunnerPlayerBase* target;

	UPROPERTY()
	class ABeastEnemy* me;

	void OnDamageProcess(int32 damage);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSM)
	int32 hp = 2;

	UPROPERTY()
	class UBeastEnemyAnim* Anim;

	bool bDieDone;

	FORCEINLINE void onDieEnd()
	{
		bDieDone = true;
	}
};
