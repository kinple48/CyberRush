// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/DroneEnemy.h"
#include "Components/BoxComponent.h"

ADroneEnemy::ADroneEnemy()
{
	boxcomp->SetBoxExtent(FVector(1.f,1.f,1000.f));
}
