#include "LJW/FloorTile.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "CyberRushCharacter.h"
#include "CyberRushGameMode.h"
#include "LJW/Item.h"

AFloorTile::AFloorTile()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshWall(TEXT("/Engine/BasicShapes/Cube.Cube"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFloor(TEXT("/Engine/BasicShapes/Cube.Cube"));
	
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MatWall(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MatFloor(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));

	Scenecomp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(Scenecomp);
	
	wall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("wall"));
	if (MeshWall.Succeeded()) wall->SetStaticMesh(MeshWall.Object);
	if (MatWall.Succeeded()) wall->SetMaterial(0, MatWall.Object);
	wall->SetRelativeScale3D(FVector(10.f,0.1f,2.0f));
	wall->SetRelativeLocation(FVector(500.0f,-500.0f,100.0f));
	wall->SetupAttachment(Scenecomp);

	wall2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("wall2"));
	if (MeshWall.Succeeded()) wall2->SetStaticMesh(MeshWall.Object);
	if (MatWall.Succeeded()) wall2->SetMaterial(0, MatWall.Object);
	wall2->SetRelativeScale3D(FVector(10.f,0.1f,2.0f));
	wall2->SetRelativeLocation(FVector(500.0f,500.0f,100.0f));
	wall2->SetupAttachment(Scenecomp);
	
	floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("floor"));
	if (MeshFloor.Succeeded()) floor->SetStaticMesh(MeshFloor.Object);
	if (MatFloor.Succeeded()) floor->SetMaterial(0, MatFloor.Object);
	floor->SetRelativeScale3D(FVector(10.0f,10.0f,0.1f));
	floor->SetRelativeLocation(FVector(500.0f,0.0f,0.0f));
	floor->SetupAttachment(Scenecomp);
	floor->SetCollisionResponseToChannel(ECC_GameTraceChannel1,ECR_Overlap);

	Arrowcomp = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrowcomp"));
	Arrowcomp->SetRelativeLocation(FVector(1000.0f,0.0f,0.0f));
	Arrowcomp->SetupAttachment(Scenecomp);

	Boxcomp = CreateDefaultSubobject<UBoxComponent>(TEXT("Boxcomp"));
	Boxcomp->SetRelativeLocation(FVector(1050.0f,0.0f,200.0f));
	Boxcomp->SetBoxExtent(FVector(32.0f,500.0f,200.0f));
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
	if (auto Player = Cast<ACyberRushCharacter>(OtherActor))
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



