// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/STitleWidget.h"

#include "LJW/MainHUD.h"

void STitleWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	
	OwningHUD = InArgs._OwningHUD;
	
	const FMargin ContentPadding = FMargin(500.f, 300.f);
	const FMargin ButtonPadding = FMargin(10.f);
	
	const FText TitleText = FText::FromString("CyberRush");
	const FText StartText = FText::FromString("Start Game");
	const FText OptionsText = FText::FromString("Options");
	const FText QuitText = FText::FromString("Quit Game");

	FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ButtonTextStyle.Size = 40.f;
	
	FSlateFontInfo TitleTextStyle = ButtonTextStyle;
	TitleTextStyle.Size = 60.f;
	
	ChildSlot
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.ColorAndOpacity(FColor::Black)
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(ContentPadding)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				[
					SNew(STextBlock)
					.Font(TitleTextStyle)
					.Text(TitleText)
					.Justification(ETextJustify::Center)
				]

				+SVerticalBox::Slot()
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &STitleWidget::OnPlayClicked)
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(StartText)
						.Justification(ETextJustify::Center)
					]
				]

				+SVerticalBox::Slot()
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(OptionsText)
						.Justification(ETextJustify::Center)
					]
				]

				+SVerticalBox::Slot()
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &STitleWidget::OnQuitClicked)
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(QuitText)
						.Justification(ETextJustify::Center)
					]
				]
			]
		];
}

FReply STitleWidget::OnPlayClicked() const
{
	if (OwningHUD.IsValid())
	{
		OwningHUD->RemoveMenu();
		OwningHUD->OpenMainWidget();
	}
	return FReply::Handled();
}

FReply STitleWidget::OnQuitClicked() const
{
	if (OwningHUD.IsValid())
	{
		if (APlayerController* PC = OwningHUD->PlayerOwner)
		{
			PC->ConsoleCommand("quit");
		}
	}
	return FReply::Handled();
}
