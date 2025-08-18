// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/TitleHUD.h"
#include "LJW/STitleWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"

void ATitleHUD::BeginPlay()
{
	Super::BeginPlay();
	ShowMenu();
}

void ATitleHUD::ShowMenu()
{
	if (GEngine && GEngine->GameViewport)
	{
		TitleWidget = SNew(STitleWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(TitleWidgetContainer,SWeakWidget).PossiblyNullContent(TitleWidget.ToSharedRef()));
		
		if (PlayerOwner)
		{
			PlayerOwner->bShowMouseCursor = true;
			PlayerOwner->SetInputMode(FInputModeUIOnly());
		}
	}
}

void ATitleHUD::RemoveMenu()
{
	if (GEngine && GEngine->GameViewport && TitleWidgetContainer.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(TitleWidgetContainer.ToSharedRef());

		if (PlayerOwner)
		{
			PlayerOwner->bShowMouseCursor = true;
			PlayerOwner->SetInputMode(FInputModeGameAndUI());
		}
	}
}

void ATitleHUD::OpenMainWidget()
{
	if (GEngine && GEngine->GameViewport)
	{
		TitleWidget = SNew(STitleWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(TitleWidgetContainer,SWeakWidget).PossiblyNullContent(TitleWidget.ToSharedRef()));
	}
}
