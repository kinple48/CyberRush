// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TitleHUD.generated.h"

/**
 * 
 */
UCLASS()
class CYBERRUSH_API ATitleHUD : public AHUD
{
	GENERATED_BODY()
protected:
	TSharedPtr<class STitleWidget> TitleWidget;
	TSharedPtr<class SWidget> TitleWidgetContainer;
	
	TSharedPtr<class SSelectWidget> SelectWidget;
	TSharedPtr<class SWidget> SelectWidgetContainer;
	
	TSharedPtr<class SShopWidget> ShopWidget;
	TSharedPtr<class SWidget> ShopWidgetContainer;
	
	TSharedPtr<class SGearUpWidget> GearUpWidget;
	TSharedPtr<class SWidget> GearUpWidgetContainer;

	UPROPERTY()
	UMaterialInstanceDynamic* GearUpMaterialInstance;
	
	virtual void BeginPlay() override;

public:
	void ShowMenu();
	void RemoveMenu();
	void OpenSelectWidget();
	void RemoveSelectWidget();
	void OpenShopWidget();
	void RemoveShopWidget();
	void OpenGearUpWidget();
	void RemoveGearUpWidget();
};
