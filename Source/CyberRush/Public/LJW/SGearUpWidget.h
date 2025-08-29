// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
/**
 * 
 */
class SGearUpWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGearUpWidget) {}
	SLATE_ARGUMENT(TWeakObjectPtr<class ATitleHUD>, OwningHUD);
	SLATE_ARGUMENT(UMaterialInstanceDynamic*, MaterialInstance);
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	
	TWeakObjectPtr<class ATitleHUD> OwningHUD;

	TSharedRef<SWidget> GenerateRow(int32 RowIndex, int32 Columns, float SlotSize, float Padding);
	
	virtual bool SupportsKeyboardFocus() const override { return true; }
	TSharedPtr<FSlateBrush> MaterialBrush;
};