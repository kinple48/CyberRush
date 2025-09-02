#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

class SGameOverWidget : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SGameOverWidget) {}
		
	SLATE_ARGUMENT(TWeakObjectPtr<class AMainHUD>, OwningHUD);
	SLATE_ARGUMENT(TWeakObjectPtr<class ARunnerPlayerBase>, OwnerCharacter)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	
	TWeakObjectPtr<class AMainHUD> OwningHUD;
	TWeakObjectPtr<class ARunnerPlayerBase> OwnerCharacter;
	
	virtual bool SupportsKeyboardFocus() const override { return true; }

private:
	FText GetScoreText() const;
	FText GetHighScoreText() const;

public:
	FReply OnReStartClicked() const;
	FReply OnQuitGameClicked() const;
};
