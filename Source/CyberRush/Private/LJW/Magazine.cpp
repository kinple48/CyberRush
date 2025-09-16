#include "LJW/Magazine.h"

#include "Components/BoxComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "HHS/PlayerCombatComponent.h"
#include "HHS/RunnerPlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "LJW/FloorTile.h"

AMagazine::AMagazine()
{
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshItem(TEXT("/Engine/BasicShapes/Cube.Cube"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MatItem(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));

	scenecomp = CreateDefaultSubobject<USceneComponent>(TEXT("scenecomp"));
	SetRootComponent(scenecomp);

	meshcomp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshcomp"));
	if (MeshItem.Succeeded()) meshcomp->SetStaticMesh(MeshItem.Object);
	if (MatItem.Succeeded()) meshcomp->SetMaterial(0, MatItem.Object);
	meshcomp->SetupAttachment(scenecomp);
	meshcomp->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	movecomp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("movecomp"));
	movecomp->RotationRate = FRotator(0.0f,180.0f,0.0f);

	boxcomp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxcomp"));
	boxcomp->SetupAttachment(scenecomp);
	boxcomp->SetBoxExtent(FVector(1.f,1.f,100.f));
	boxcomp->SetCollisionProfileName(TEXT("ItemChecker"));
}

void AMagazine::BeginPlay()
{
	Super::BeginPlay();
	meshcomp->OnComponentBeginOverlap.AddDynamic(this, &AMagazine::OnItemBeginOverlap);
	boxcomp->OnComponentEndOverlap.AddDynamic(this, &AMagazine::OnItemEndOverlap);
}

void AMagazine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMagazine::OnItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto Player = Cast<ARunnerPlayerBase>(OtherActor))
	{
		UGameplayStatics::PlaySound2D(GetWorld(),ItemSound);

		if (Player->CombatComp)
		{
			int32& CurrentReserve = Player->CombatComp->ReserveAmmo;
			int32 MaxReserve = Player->CombatComp->maxReserveAmmo;

			const int32 IncreaseAmount = 8;

			CurrentReserve = FMath::Clamp(CurrentReserve + IncreaseAmount, 0, MaxReserve);
		}
		
		Destroy();
	}
}

void AMagazine::OnItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (auto Floor = Cast<AFloorTile>(OtherActor))
	{
		Destroy();
	}
}