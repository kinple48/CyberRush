// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/FloorTileType2.h"
#include "LJW/Obstacle.h"

void AFloorTileType2::SpawnObjectLine()
{
	int32 LaneIndex = FMath::RandRange(0, LaneYPositions.Num() - 1); 
	FVector SpawnLocation;
	float RandomXOffset = FMath::FRandRange(-100.f, 100.f);

	SpawnLocation.X = GetActorLocation().X + RandomXOffset;
	SpawnLocation.Y = GetActorLocation().Y;
	SpawnLocation.Z = GetActorLocation().Z;
	FActorSpawnParameters SpawnParams; SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<AObstacle>(ObstacleFactory, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
	
}