// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/Item.h"

#include "CyberRushCharacter.h"
#include "CyberRushGameMode.h"
#include "Components/BoxComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "HHS/RunnerPlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "LJW/FloorTile.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	meshcomp->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnItemBeginOverlap);
	boxcomp->OnComponentEndOverlap.AddDynamic(this, &AItem::OnItemEndOverlap);
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::OnItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto Player = Cast<ARunnerPlayerBase>(OtherActor))
	{
		AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
		if (GameModeBase)
		{
			if (ACyberRushGameMode* MyGameMode = Cast<ACyberRushGameMode>(GameModeBase))
			{
				MyGameMode->AddScore(ScoreItem);
			}
		}
		
		UGameplayStatics::PlaySound2D(GetWorld(),ItemSound);
		Player->CurrentCoin += 1;
		Destroy();
	}
}

void AItem::OnItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//if (auto Floor = Cast<AFloorTile>(OtherActor))
	//{
	//	Destroy();
	//}
}

