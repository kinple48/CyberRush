// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CyberRushSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CYBERRUSH_API UCyberRushSaveGame : public ULocalPlayerSaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	int32 HighScoreSave;
};
