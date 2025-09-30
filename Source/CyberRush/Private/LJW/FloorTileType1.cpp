#include "LJW/FloorTileType1.h"
#include "LJW/Item.h"
AFloorTileType1::AFloorTileType1()
{

}

void AFloorTileType1::BeginPlay()
{
	Super::BeginPlay();
}

void AFloorTileType1::SpawnItemLine()
{
	int32 LaneIndex = FMath::RandRange(0, LaneYPositions.Num() - 1); 
	float CoinSpacing = 200.f; 
	int32 CoinCount = 10;
	
	for (int32 i = 0; i < CoinCount; i++)
	{
		FVector SpawnLocation;
		SpawnLocation.X = GetActorLocation().X + (i * CoinSpacing);
		SpawnLocation.Y = LaneYPositions[LaneIndex];
		SpawnLocation.Z = GetActorLocation().Z + 100.f;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<AItem>(ItemFactory, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
	}
}