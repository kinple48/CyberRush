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

	virtual void BeginPlay() override;

public:
	void ShowMenu();
	void RemoveMenu();
	void OpenMainWidget();
};
