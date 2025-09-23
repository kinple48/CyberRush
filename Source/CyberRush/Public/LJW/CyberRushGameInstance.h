// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CyberRushGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CYBERRUSH_API UCyberRushGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	float BGMVolume = 0.5f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	float SFXVolume = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	float MasterVolume = 0.5f;
	
	UFUNCTION(BlueprintCallable)
	void ApplyAudioSettings(UWorld* LocalWorldContext);

	UFUNCTION(BlueprintPure, Category = "Game Instance")
	UWorld* GetTheWorld() const;

	UPROPERTY(BlueprintReadWrite, Category = "Audio")
	TObjectPtr<UAudioComponent> BGM_AudioComponent;
};
