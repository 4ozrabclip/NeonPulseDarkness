// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/NPD_DialogueWidget.h"

#include "Components/TextBlock.h"

void UNPD_DialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UNPD_DialogueWidget::SetText(FColor TextColour, const FString& InText)
{
	DialogueText->SetColorAndOpacity(TextColour);
	DialogueText->SetText(FText::FromString(InText));
}
