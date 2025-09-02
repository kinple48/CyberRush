#include "LJW/SGameOverWidget.h"

#include "CyberRushGameMode.h"
#include "HHS/RunnerPlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "LJW/MainHUD.h"


void SGameOverWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;

	OwningHUD = InArgs._OwningHUD;
	OwnerCharacter = InArgs._OwnerCharacter;

	const FMargin ContentPadding = FMargin(500.f, 300.f);
	const FMargin ButtonPadding = FMargin(30.f);
	const FMargin TextPadding = FMargin(10.f);
	
	const FText TitleText = FText::FromString("GameOver");
	const FText ReStartText = FText::FromString("     RestartGame     ");
	const FText QuitText = FText::FromString("     QuitGame     ");

	FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ButtonTextStyle.Size = 40.f;
	
	FSlateFontInfo TitleTextStyle = ButtonTextStyle;
	TitleTextStyle.Size = 80.f;
	
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
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			.Padding(50.f)
			[
				SNew(STextBlock)
				.Font(TitleTextStyle)
				.Text(TitleText)
				.Justification(ETextJustify::Center)
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Fill)
			.Padding(ContentPadding)
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.Padding(TextPadding)
				.AutoHeight()
				[
					SNew(STextBlock)
					.Font(ButtonTextStyle)
					.Text(this, &SGameOverWidget::GetScoreText)
					.Justification(ETextJustify::Center)
				]
				+SVerticalBox::Slot()
				.Padding(TextPadding)
				.AutoHeight()
				[
					SNew(STextBlock)
					.Font(ButtonTextStyle)
					.Text(this, &SGameOverWidget::GetHighScoreText)
					.Justification(ETextJustify::Center)
				]
				+SVerticalBox::Slot()
				.Padding(FMargin(80.f))
				+SVerticalBox::Slot()
				.Padding(ButtonPadding)
				.AutoHeight()
				[
					SNew(SButton)
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.OnClicked(this, &SGameOverWidget::OnReStartClicked)
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(ReStartText)
						.Justification(ETextJustify::Center)
					]
				]

				+SVerticalBox::Slot()
				.Padding(ButtonPadding)
				.AutoHeight()
				[
					SNew(SButton)
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.OnClicked(this, &SGameOverWidget::OnQuitGameClicked)
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

FText SGameOverWidget::GetScoreText() const
{
	if (OwningHUD.IsValid())
	{
		if (ACyberRushGameMode* MyGameMode = Cast<ACyberRushGameMode>(UGameplayStatics::GetGameMode(OwningHUD.Get())))
		{
			FFormatNamedArguments Args;
			Args.Add(TEXT("Score"), FText::AsNumber(MyGameMode->CurrentScore));
			return FText::Format(FText::FromString(TEXT("Score : {Score}")), Args);
		}
	}
	return FText::FromString(TEXT("Score : 0"));
}

FText SGameOverWidget::GetHighScoreText() const
{
	if (OwningHUD.IsValid())
	{
		if (ACyberRushGameMode* MyGameMode = Cast<ACyberRushGameMode>(UGameplayStatics::GetGameMode(OwningHUD.Get())))
		{
			FFormatNamedArguments Args;
			Args.Add(TEXT("HighScore"), FText::AsNumber(MyGameMode->HighScore));
			return FText::Format(FText::FromString(TEXT("HighScore : {HighScore}")), Args);
		}
	}
	return FText::FromString(TEXT("HighScore : 0"));
}

FReply SGameOverWidget::OnReStartClicked() const
{
	if (OwningHUD.IsValid())
	{
		FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(OwningHUD.Get());
		UGameplayStatics::OpenLevel(OwningHUD.Get(), FName(*CurrentLevelName));
	}
	return FReply::Handled();
}

FReply SGameOverWidget::OnQuitGameClicked() const
{
	if (OwningHUD.IsValid())
	{
		OwningHUD->RemoveGameOverUI();
		if (APlayerController* PC = OwningHUD->PlayerOwner)
		{
			UGameplayStatics::OpenLevel(PC, FName("LobbyLevel"));
		}
	}
	return FReply::Handled();
}


