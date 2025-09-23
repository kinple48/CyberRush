#include "LJW/Obstacle.h"

#include "Components/BoxComponent.h"
#include "HHS/RunnerPlayerBase.h"
#include "LJW/FloorTile.h"
#include "HHS/PlayerMoveComponent.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;
	scenecomp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(scenecomp);
	
	boxcomp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	boxcomp->SetupAttachment(RootComponent);
	boxcomp->SetBoxExtent(FVector(200, 100, 100));

	boxcomp2 = CreateDefaultSubobject<UBoxComponent>(TEXT("boxcomp2"));
	boxcomp2->SetupAttachment(RootComponent);
	boxcomp2->SetBoxExtent(FVector(1.f,1.f,100.f));
	boxcomp2->SetCollisionProfileName(TEXT("ItemChecker"));

}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	boxcomp->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnBoxOverlap);
	boxcomp2->OnComponentEndOverlap.AddDynamic(this, &AObstacle::OnItemEndOverlap);
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacle::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto player = Cast<ARunnerPlayerBase>(OtherActor);
	if (player)
	{
		player->DamageProcess();
	}
}

void AObstacle::OnItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (auto Floor = Cast<AFloorTile>(OtherActor))
	{
		Destroy();
	}
}

