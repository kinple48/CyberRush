// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/MainHUD.h"

#include "SInGameMenu.h"
#include "LJW/SMainWidget.h"
#include "LJW/STitleWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "HHS/RunnerPlayerBase.h"
#include "LJW/SGameOverWidget.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine && GEngine->GameViewport)
	{
		MainWidget = SNew(SMainWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MainWidgetContainer,SWeakWidget).PossiblyNullContent(MainWidget.ToSharedRef()));
	}

	if (APlayerController* PC = GetOwningPlayerController())
	{
		PC->SetInputMode(FInputModeGameAndUI());
		PC->bShowMouseCursor = true;
	}
	FSlateApplication::Get().SetUserFocusToGameViewport(0);
}

void AMainHUD::ShowMenu()
{
	
	InGameMenu = SNew(SInGameMenu).OwningHUD(this);
	GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(InGameMenuContainer,SWeakWidget).PossiblyNullContent(InGameMenu.ToSharedRef()));
	
	if (APlayerController* PC = GetOwningPlayerController())
	{
		PC->SetPause(true);
		PC->SetInputMode(FInputModeGameAndUI());
		PC->bShowMouseCursor = true;
	}
}

void AMainHUD::RemoveMenu()
{
	if (GEngine && GEngine->GameViewport && InGameMenuContainer.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(InGameMenuContainer.ToSharedRef());

		if (PlayerOwner)
		{
			PlayerOwner->bShowMouseCursor = true;
			PlayerOwner->SetInputMode(FInputModeGameAndUI());
		}
	}
}

void AMainHUD::QuitGame()
{
	if (GEngine && GEngine->GameViewport && MainWidgetContainer.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(MainWidgetContainer.ToSharedRef());

		if (PlayerOwner)
		{
			PlayerOwner->bShowMouseCursor = true;
			PlayerOwner->SetInputMode(FInputModeGameAndUI());
		}
	}
}

void AMainHUD::ShowGameOverUI()
{
	if (GEngine && GEngine->GameViewport)
	{
		GameOverWidget = SNew(SGameOverWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(GameOverWidgetContainer,SWeakWidget).PossiblyNullContent(GameOverWidget.ToSharedRef()));
		
		if (PlayerOwner)
		{
			PlayerOwner->bShowMouseCursor = true;
			PlayerOwner->SetInputMode(FInputModeUIOnly());
		}
	}
}

void AMainHUD::RemoveGameOverUI()
{
	if (GEngine && GEngine->GameViewport && GameOverWidgetContainer.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(GameOverWidgetContainer.ToSharedRef());

		if (PlayerOwner)
		{
			PlayerOwner->bShowMouseCursor = true;
			PlayerOwner->SetInputMode(FInputModeGameAndUI());
		}
	}
}



