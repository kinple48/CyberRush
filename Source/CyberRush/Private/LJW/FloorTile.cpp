#include "LJW/FloorTile.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "CyberRushCharacter.h"
#include "CyberRushGameMode.h"
#include "HHS/RunnerPlayerBase.h"
#include "LJW/Item.h"

AFloorTile::AFloorTile()
{
	PrimaryActorTick.bCanEverTick = true;

	Scenecomp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(Scenecomp);
	
	floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("floor"));
	floor->SetupAttachment(Scenecomp);
	floor->SetCollisionResponseToChannel(ECC_GameTraceChannel1,ECR_Overlap);

	Arrowcomp = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrowcomp"));
	Arrowcomp->SetupAttachment(Scenecomp);

	Boxcomp = CreateDefaultSubobject<UBoxComponent>(TEXT("Boxcomp"));
	Boxcomp->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	Boxcomp->SetupAttachment(Scenecomp);
}

// Called when the game starts or when spawned
void AFloorTile::BeginPlay()
{
	Super::BeginPlay();
	Boxcomp->OnComponentBeginOverlap.AddDynamic(this, &AFloorTile::OnBoxBeginOverlap);
}

// Called every frame
void AFloorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FTransform AFloorTile::GetAttachTransform()
{
	FTransform AttachTransform = Arrowcomp->GetComponentTransform();
	return AttachTransform;
}

void AFloorTile::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto Player = Cast<ARunnerPlayerBase>(OtherActor))
	{
		if (auto* GM = GetWorld()->GetAuthGameMode<ACyberRushGameMode>())
		{
			GM->AddFloorTile();
			FTimerHandle DestroyHandle;
			GetWorld()->GetTimerManager().SetTimer(
				DestroyHandle,
				[this]()
				{
					Destroy();
				},
				2.0f,
				false
			);
		}
	}
}



