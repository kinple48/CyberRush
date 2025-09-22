// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/DroneEnemy.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "LJW/DroneEnemyFSM.h"

ADroneEnemy::ADroneEnemy()
{
	boxcomp->SetBoxExtent(FVector(1.f,1.f,1000.f));
	FSM = CreateDefaultSubobject<UDroneEnemyFSM>(TEXT("FSM"));
	ReticleDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("ReticleDecal"));
	ReticleDecal->SetupAttachment(RootComponent);
	ReticleDecal->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	ReticleDecal->DecalSize = FVector(64.f, 64.f, 64.f);
	ReticleDecal->SetVisibility(false);
}

void ADroneEnemy::BeginPlay()
{
	Super::BeginPlay();
	if (ReticleMaterial)
	{
		ReticleDecal->SetDecalMaterial(ReticleMaterial);
	}
}
