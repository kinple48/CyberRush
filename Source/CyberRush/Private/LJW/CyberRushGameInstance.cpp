// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/CyberRushGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"

void UCyberRushGameInstance::ApplyAudioSettings(UWorld* LocalWorldContext)
{
	
	if (!LocalWorldContext) return;
	USoundMix* Mix = LoadObject<USoundMix>(nullptr, TEXT("/Game/LJW/Sound/MasterSoundMix.MasterSoundMix"));
	if (!Mix) return;
	USoundClass* BGM = LoadObject<USoundClass>(nullptr, TEXT("/Game/LJW/Sound/BGM.BGM"));
	USoundClass* SFX = LoadObject<USoundClass>(nullptr, TEXT("/Game/LJW/Sound/SFX.SFX"));
	USoundClass* Master = LoadObject<USoundClass>(nullptr, TEXT("/Game/LJW/Sound/MasterSound.MasterSound"));
	if (!Master || !BGM || !SFX) return;
	UGameplayStatics::ClearSoundMixModifiers(LocalWorldContext);
    
	UGameplayStatics::PushSoundMixModifier(LocalWorldContext, Mix);
    
	UGameplayStatics::SetSoundMixClassOverride(LocalWorldContext, Mix, BGM, BGMVolume, 1.0f, 0.f, false);
	UGameplayStatics::SetSoundMixClassOverride(LocalWorldContext, Mix, SFX, SFXVolume, 1.0f, 0.f, false);
	UGameplayStatics::SetSoundMixClassOverride(LocalWorldContext, Mix, Master, MasterVolume, 1.0f, 0.f, true);
}

UWorld* UCyberRushGameInstance::GetTheWorld() const
{
	return GetWorld();
}
