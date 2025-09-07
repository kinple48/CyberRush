// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/BeastEnemy.h"

#include "Components/SphereComponent.h"

ABeastEnemy::ABeastEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionRange->SetSphereRadius(90.f);
}

void ABeastEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABeastEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABeastEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

