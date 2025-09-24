#include "LJW/Rocket.h"

#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Components/SphereComponent.h"
#include "HHS/PlayerMoveComponent.h"
#include "HHS/RunnerPlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "LJW/FloorTile.h"

ARocket::ARocket()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(15.f);
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	RootComponent = CollisionComp;

	RocketMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RocketMesh"));
	RocketMesh->SetupAttachment(CollisionComp);
}

void ARocket::BeginPlay()
{
	Super::BeginPlay();
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ARocket::OnOverlap);
	GetWorld()->GetTimerManager().SetTimer(
	   AutoDestroyHandle,
	   this,
	   &ARocket::SelfDestruct,
	   0.5f,
	   false
   );
}

void ARocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!MoveDirection.IsNearlyZero())
	{
		FVector NewLocation = GetActorLocation() + MoveDirection * Speed * DeltaTime;
		SetActorLocation(NewLocation);
		FRotator FireRotation = MoveDirection.Rotation();
		FireRotation.Pitch -= 0.35f;
		MoveDirection = FireRotation.Vector();
	}
}

void ARocket::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ARunnerPlayerBase* player = Cast<ARunnerPlayerBase>(OtherActor))
	{
		player->DamageProcess();
		UGameplayStatics::PlaySound2D(GetWorld(), ExplosionSound);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionVFX, GetActorLocation());
		Destroy();
	}
}

void ARocket::Init(FVector InDirection)
{
	MoveDirection = InDirection;
}

void ARocket::SelfDestruct()
{
	UGameplayStatics::PlaySound2D(GetWorld(), ExplosionSound);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionVFX, GetActorLocation());
	Destroy();
}

