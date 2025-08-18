#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

class SMainWidget : public SCompoundWidget
{
	
public:

	SLATE_BEGIN_ARGS(SMainWidget) {}
		
	SLATE_ARGUMENT(TWeakObjectPtr<class AMainHUD>, OwningHUD);

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	FReply OnMenuClicked() const;
	
	TWeakObjectPtr<class AMainHUD> OwningHUD;

	virtual bool SupportsKeyboardFocus() const override { return true; }
};
