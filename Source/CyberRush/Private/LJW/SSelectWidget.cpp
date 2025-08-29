// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/SSelectWidget.h"
#include "LJW/STitleWidget.h"
#include "Kismet/GameplayStatics.h"
#include "LJW/TitleHUD.h"

void SSelectWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	
	OwningHUD = InArgs._OwningHUD;
	
	const FMargin ContentPadding = FMargin(500.f, 300.f);
	const FMargin ButtonPadding = FMargin(10.f);
	
	const FText TitleText = FText::FromString("CyberRush");
	const FText PlayText = FText::FromString("Play/Run!");
	const FText SettingText = FText::FromString("Gear Up");
	const FText ShopText = FText::FromString("Shop");

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
					.OnClicked(this, &SSelectWidget::OnPlayClicked)
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(PlayText)
						.Justification(ETextJustify::Center)
					]
				]

				+SVerticalBox::Slot()
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SSelectWidget::OnGearUpClicked)
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(SettingText)
						.Justification(ETextJustify::Center)
					]
				]

				+SVerticalBox::Slot()
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					//.OnClicked(this, &STitleWidget::OnQuitClicked)
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(ShopText)
						.Justification(ETextJustify::Center)
					]
				]
			]
		];
}

FReply SSelectWidget::OnPlayClicked() const
{
	if (OwningHUD.IsValid())
	{
		OwningHUD->RemoveSelectWidget();
		if (APlayerController* PC = OwningHUD->PlayerOwner)
		{
			UGameplayStatics::OpenLevel(PC, FName("TestMap"));
		}
	}
	
	return FReply::Handled();
}

FReply SSelectWidget::OnGearUpClicked() const
{
	if (OwningHUD.IsValid())
	{
		OwningHUD->RemoveSelectWidget();
		UE_LOG(LogTemp, Warning, TEXT("close widget"));
		OwningHUD->OpenGearUpWidget();
		UE_LOG(LogTemp, Warning, TEXT("open widget"));
	}
	return FReply::Handled();
}

FReply SSelectWidget::OnShopClicked() const
{
	return FReply::Handled();
}
