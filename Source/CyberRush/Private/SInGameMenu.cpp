#include "SInGameMenu.h"
#include "HHS/RunnerPlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "LJW/MainHUD.h"


void SInGameMenu::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	
	OwningHUD = InArgs._OwningHUD;
	OwnerCharacter = InArgs._OwnerCharacter;
	
	const FMargin ContentPadding = FMargin(500.f, 300.f);
	const FMargin ButtonPadding = FMargin(10.f);
	
	const FText MenuText = FText::FromString("Menu");
	const FText ResumeGameText = FText::FromString("Resume Game");
	const FText OptionsText = FText::FromString("Options");
	const FText QuitGameText = FText::FromString("Quit Game");

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
				.ColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, 0.5f))
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
					.Text(MenuText)
					.Justification(ETextJustify::Center)
				]

				+SVerticalBox::Slot()
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SInGameMenu::OnResumeGameClicked)
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(ResumeGameText)
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
					.OnClicked(this, &SInGameMenu::OnQuitGameClicked)
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(QuitGameText)
						.Justification(ETextJustify::Center)
					]
				]
			]
		];
}

FReply SInGameMenu::OnResumeGameClicked() const
{
	if (APlayerController* PC = OwningHUD->PlayerOwner)
	{
		PC->SetPause(false);
	}
	
	OwningHUD->RemoveMenu();
	return FReply::Handled();
}

FReply SInGameMenu::OnOptionsClicked() const
{
	return FReply::Handled();
}

FReply SInGameMenu::OnQuitGameClicked() const
{
	if (OwningHUD.IsValid())
	{
		OwningHUD->QuitGame();
		if (APlayerController* PC = OwningHUD->PlayerOwner)
		{
			UGameplayStatics::OpenLevel(PC, FName("LobbyLevel")); // GameLevel은 맵 이름
		}
	}
	return FReply::Handled();
}
