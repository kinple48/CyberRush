// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/MainHUD.h"
#include "LJW/SMainWidget.h"
#include "LJW/STitleWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();
	ShowMenu();
}

void AMainHUD::ShowMenu()
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

void AMainHUD::RemoveMenu()
{
	if (GEngine && GEngine->GameViewport && TitleWidgetContainer.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(TitleWidgetContainer.ToSharedRef());

		if (PlayerOwner)
		{
			PlayerOwner->bShowMouseCursor = false;
			PlayerOwner->SetInputMode(FInputModeGameOnly());
		}
	}
}

void AMainHUD::OpenMainWidget()
{
	if (GEngine && GEngine->GameViewport)
	{
		MainWidget = SNew(SMainWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MainWidgetContainer,SWeakWidget).PossiblyNullContent(MainWidget.ToSharedRef()));
	}
}



