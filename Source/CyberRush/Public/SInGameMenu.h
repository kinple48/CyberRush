// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

/**
 * 
 */
class SInGameMenu : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SInGameMenu) {}
		
	SLATE_ARGUMENT(TWeakObjectPtr<class AMainHUD>, OwningHUD);
	SLATE_ARGUMENT(TWeakObjectPtr<class ARunnerPlayerBase>, OwnerCharacter)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	
	TWeakObjectPtr<class AMainHUD> OwningHUD;
	TWeakObjectPtr<class ARunnerPlayerBase> OwnerCharacter;
	
	FReply OnResumeGameClicked() const;
	FReply OnOptionsClicked() const;
	FReply OnQuitGameClicked() const;
	
	virtual bool SupportsKeyboardFocus() const override { return true; }
};
