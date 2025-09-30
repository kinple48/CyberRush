// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/DroneEnemyAnim.h"

#include "Kismet/GameplayStatics.h"
#include "LJW/DroneEnemy.h"


void UDroneEnemyAnim::AnimNotify_Die()
{
	ADroneEnemy* enemy = Cast<ADroneEnemy>(TryGetPawnOwner());
	if (enemy)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), enemy->ExplosionSound);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), enemy->ExplosionVFX ,enemy->GetActorLocation());
		enemy->Destroy();
	}
}
