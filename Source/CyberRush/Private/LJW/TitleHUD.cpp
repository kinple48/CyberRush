// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/TitleHUD.h"
#include "LJW/STitleWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "LJW/SGearUpWidget.h"
#include "LJW/SSelectWidget.h"
#include "LJW/SShopWidget.h"

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

void ATitleHUD::OpenSelectWidget()
{
	if (GEngine && GEngine->GameViewport)
	{
		SelectWidget = SNew(SSelectWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(SelectWidgetContainer,SWeakWidget).PossiblyNullContent(SelectWidget.ToSharedRef()));
	}
}

void ATitleHUD::RemoveSelectWidget()
{
	if (GEngine && GEngine->GameViewport && SelectWidgetContainer.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(SelectWidgetContainer.ToSharedRef());

		if (PlayerOwner)
		{
			PlayerOwner->bShowMouseCursor = true;
			PlayerOwner->SetInputMode(FInputModeGameAndUI());
		}
	}
}

void ATitleHUD::OpenShopWidget()
{
	if (GEngine && GEngine->GameViewport)
	{
		ShopWidget = SNew(SShopWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(ShopWidgetContainer,SWeakWidget).PossiblyNullContent(SelectWidget.ToSharedRef()));
	}
}

void ATitleHUD::RemoveShopWidget()
{
	
}

void ATitleHUD::OpenGearUpWidget()
{
	if (GEngine && GEngine->GameViewport)
	{
		GearUpWidget = SNew(SGearUpWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(SelectWidgetContainer,SWeakWidget).PossiblyNullContent(SelectWidget.ToSharedRef()));
	}
}

void ATitleHUD::RemoveGearUpWidget()
{
	
}
