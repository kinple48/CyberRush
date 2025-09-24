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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Runner|Movement")
	int32 CurrentLane = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Runner|Movement")
	float LaneDistance = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Runner|Movement")
	float LaneInterpSpeed = 10.f;

	void MoveLeft();
	void MoveRight();
	void UpdateLanePosition(float DeltaTime);

	void Jump();

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

	bool bCanRun = false;

	UPROPERTY()
	class UPlayerAnimInstance* Anim;

	FTimerHandle LaneCooldownHandle;
    
    bool bCanChangeLane = true;
    float LaneChangeCooldown = 0.4f;

	void ResetLaneCooldown();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundBase* JumpSound;
};
