// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rocket.generated.h"

UCLASS()
class CYBERRUSH_API ARocket : public AActor
{
	GENERATED_BODY()
	
public:
	ARocket();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* RocketMesh;
	
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* BulletMovement;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* CollisionComp;
	
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Init(FVector InDirection);
	UPROPERTY(EditAnywhere, Category="Rocket")
	float Speed = 2000.f;

	FVector MoveDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundBase* ExplosionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	class UParticleSystem* ExplosionVFX;
	
	FTimerHandle AutoDestroyHandle;
	void SelfDestruct();
};
