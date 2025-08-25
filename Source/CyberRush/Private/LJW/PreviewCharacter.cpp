// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/PreviewCharacter.h"

#include "Components/PointLightComponent.h"
#include "Components/SceneCaptureComponent2D.h"

// Sets default values
APreviewCharacter::APreviewCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("CaptureComponent"));
	CaptureComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APreviewCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APreviewCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APreviewCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

