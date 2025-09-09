#include "LJW/Obstacle.h"

#include "Components/BoxComponent.h"
#include "HHS/RunnerPlayerBase.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;
	scenecomp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(scenecomp);
	
	boxcomp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	boxcomp->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnBoxOverlap);
	boxcomp->SetupAttachment(RootComponent);
	boxcomp->SetBoxExtent(FVector(200, 100, 100));
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacle::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("dead"));
	auto player = Cast<ARunnerPlayerBase>(OtherActor);
	if (player)
	{
		player->bIsDead = true;
		UE_LOG(LogTemp, Warning, TEXT("Obstacle is dead"));
	}
}

