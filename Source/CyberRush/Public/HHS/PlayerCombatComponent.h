// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnhancedInputComponent.h"
#include "PlayerCombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CYBERRUSH_API UPlayerCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerCombatComponent();

protected:
	virtual void BeginPlay() override;

public:
	void SetupInputBinding(UEnhancedInputComponent* InputComponent);

	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_Fire;
	
	UFUNCTION(BlueprintCallable, Category="Input")
	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class ABullet> BulletClass;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FVector MuzzleOffset = FVector(100.f, 0.f, 50.f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	class UArrowComponent* FirePositionComp;
	
	// ========== Object Pool ==========
	UPROPERTY(EditAnywhere, Category="Combat")
	int32 MaxBulletCount = 20;

	UPROPERTY()
	TArray<class ABullet*> Magazine;

	class ARunnerPlayerBase* Player;
	class UPlayerAnimInstance* Anim;
	
	void MakeBullet();    // 총알 풀 초기화

	FTimerHandle AttackStateResetTimer;
	float AttackResetTime = 3.0f;
	void ResetAttack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool isMoving = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	class USoundBase* FireSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	float FireRate = 0.3f;
	
	FTimerHandle FireCooldownTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	bool bCanFire = true;
};
