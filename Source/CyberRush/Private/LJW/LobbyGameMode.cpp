// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/LobbyGameMode.h"
#include "LJW/TitleHUD.h"
#include "LJW/MainPlayerController.h"

ALobbyGameMode::ALobbyGameMode()
{
	PlayerControllerClass = AMainPlayerController::StaticClass();
	HUDClass = ATitleHUD::StaticClass();
}

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();
}

