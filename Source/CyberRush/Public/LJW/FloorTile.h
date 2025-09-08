// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorTile.generated.h"

UCLASS()
class CYBERRUSH_API AFloorTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class USceneComponent* Scenecomp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* floor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* Arrowcomp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* Boxcomp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AItem> ItemFactory;
	
	FTransform GetAttachTransform();
	
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
