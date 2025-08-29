// Fill out your copyright notice in the Description page of Project Settings.


#include "LJW/SGearUpWidget.h"


void SGearUpWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	
	OwningHUD = InArgs._OwningHUD;
	
	const FMargin ContentPadding = FMargin(500.f, 300.f);
	const FMargin ButtonPadding = FMargin(10.f);
	
	const FText TitleText = FText::FromString("CyberRush");
	const FText SettingText = FText::FromString("Settings");
	const FText OptionsText = FText::FromString("2");
	const FText QuitText = FText::FromString("X");
	const FButtonStyle& ButtonStyle = FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("Button");
	
	FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ButtonTextStyle.Size = 40.f;
	
	FSlateFontInfo TitleTextStyle = ButtonTextStyle;
	TitleTextStyle.Size = 60.f;

	const int32 GridSize = 5;
	const float SlotSize = 170.0f;
	const float SlotPadding = 7.0f;
	//const FMargin ContentPadding = FMargin(4.f);

	TSharedRef<SVerticalBox> InventoryGrid = SNew(SVerticalBox);

	for (int32 Row = 0; Row < GridSize-1; ++Row)
	{
		InventoryGrid->AddSlot()
		.AutoHeight()
		.Padding(0, SlotPadding)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.AutoWidth()
			[
				GenerateRow(Row, GridSize, SlotSize, SlotPadding)
			]
		];
	}
	
	UMaterialInterface* BaseMaterial = LoadObject<UMaterialInterface>(
		nullptr,
		TEXT("/Script/Engine.Material'/Game/LJW/UI/M_CharacterPreview_UI.M_CharacterPreview_UI'")
	);

	UMaterialInstanceDynamic* MID = InArgs._MaterialInstance;

	if (MID)
	{
		MaterialBrush = MakeShared<FSlateBrush>();
		MaterialBrush->SetResourceObject(MID);
		MaterialBrush->ImageSize = FVector2D(512.f, 512.f);
	}

	
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
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Top)
				.Padding(0.f,50.f,0.f,0.f)
				[
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					.Padding(700.f,0.f,100.f,0.f)
					.AutoWidth()
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(SettingText)
						.Justification(ETextJustify::Center)
					]
					+SHorizontalBox::Slot()
					.HAlign(HAlign_Right)
					.Padding(1200.f,0.f,0.f,0.f)
					.AutoWidth()
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						[
							SNew(STextBlock)
							.Font(ButtonTextStyle)
							.Text(QuitText)
							.Justification(ETextJustify::Center)
						]
					]
				]

				+SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(10.f,100.f,10.f,200.f)
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot()
					.HAlign(HAlign_Left)
					.Padding(200.f,0.f,0.f,0.f)
					.AutoWidth()
					[
						SNew(SBox)
						.WidthOverride(800.f)
						.HeightOverride(400.f)
						[
							SNew(SImage)
							.Image(MaterialBrush.IsValid() ? MaterialBrush.Get() : nullptr)
						]		
					]
					+SHorizontalBox::Slot()
					.HAlign(HAlign_Right)
					.Padding(0.f,0.f,150.f,0.f)
					[
						SNew(SVerticalBox)
						+SVerticalBox::Slot()
						[
							SNew(SHorizontalBox)
							+SHorizontalBox::Slot()
							.AutoWidth()
							[
								SNew(SButton)
								.HAlign(HAlign_Center)
								.VAlign(VAlign_Center)
								[
									SNew(STextBlock)
									.Font(ButtonTextStyle)
									.Text(FText::FromString("Characters"))
									.Justification(ETextJustify::Center)
								]
							]
							+SHorizontalBox::Slot()
							.AutoWidth()
							[
								SNew(SButton)
								.HAlign(HAlign_Center)
								.VAlign(VAlign_Center)
								[
									SNew(STextBlock)
									.Font(ButtonTextStyle)
									.Text(FText::FromString("Weapons"))
									.Justification(ETextJustify::Center)
								]
							]
						]
						+SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(SBorder)
							.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
							.BorderBackgroundColor(ButtonStyle.Normal.TintColor)
							[
								InventoryGrid
							]
						]
					]
					
				]

			]
		];
}

TSharedRef<SWidget> SGearUpWidget::GenerateRow(int32 RowIndex, int32 Columns, float SlotSize, float Padding)
{
	TSharedRef<SHorizontalBox> RowBox = SNew(SHorizontalBox);

	for (int32 Col = 0; Col < Columns; ++Col)
	{
		int32 SlotIndex = RowIndex * Columns + Col;
		FString ItemName = FString::Printf(TEXT("Slot %d"), SlotIndex + 1);

		RowBox->AddSlot()
		.AutoWidth()
		.Padding(Padding,0.f,Padding,0.f)
		[
			SNew(SBorder)
			.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
			.BorderBackgroundColor(FLinearColor::Gray) 
			[
				SNew(SBox)
				.WidthOverride(SlotSize)
				.HeightOverride(SlotSize)
				[
					SNew(STextBlock)
					.Text(FText::FromString(ItemName))
					.Justification(ETextJustify::Center)
				
				]
			]
		];
	}

	return RowBox;
}
