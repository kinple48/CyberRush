// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/SMainWidget.h"
#include "LJW/MainHUD.h"

void SMainWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	
	OwningHUD = InArgs._OwningHUD;

	FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ButtonTextStyle.Size = 40.f;
	
	ChildSlot
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Top)
			.Padding(50.f)
			[
				SNew(SBox)
				.HeightOverride(80.f)
				.WidthOverride(80.f)
				[
					SNew(SVerticalBox)
					+SVerticalBox::Slot()
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						[
							SNew(STextBlock)
							.Text(FText::FromString("X"))
							.Font(ButtonTextStyle)
							.Justification(ETextJustify::Center)
						]
					]
				]
			]
		];
}

FReply SMainWidget::OnMenuClicked() const
{
	OwningHUD->ShowMenu();
	return FReply::Handled();
}
