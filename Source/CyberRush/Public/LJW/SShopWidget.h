// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
/**
 * 
 */
class SShopWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SShopWidget) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class ATitleHUD>, OwningHUD);

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	
	TWeakObjectPtr<class ATitleHUD> OwningHUD;

	virtual bool SupportsKeyboardFocus() const override { return true; }
};
