// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class CYBERRUSH_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BulletMesh;
	
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* BulletMovement;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* CollisionComp;


	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
				   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
				   bool bFromSweep, const FHitResult& SweepResult);

public:
	void SetActive(bool bValue);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Runner|Score")
	int32 ScoreOnHit = 100;
};
