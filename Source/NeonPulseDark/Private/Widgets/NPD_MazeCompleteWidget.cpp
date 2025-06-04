// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/NPD_MazeCompleteWidget.h"

#include "Components/TextBlock.h"
#include "NeonPulseDark/Public/Game/NPD_GameInstance.h"

void UNPD_MazeCompleteWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ProcessClearData();
	PlayAnimation(FadeInMazeCleared);
	PlayAnimation(FadeInClearData);
	
}

void UNPD_MazeCompleteWidget::NativeDestruct()
{
	Super::NativeDestruct();
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void UNPD_MazeCompleteWidget::ProcessClearData()
{
	if (!GameInstance)
		GameInstance = Cast<UNPD_GameInstance>(GetWorld()->GetGameInstance());

	FLevelData ClearedMaze = GameInstance->GetCurrentLevelData();

	float TimeCompletedPercentage = ClearedMaze.CompletionData.TimeTaken / ClearedMaze.GetTimeLimit();

	FString ClearedMazeText;

	if (TimeCompletedPercentage < 0.2f)
	{
		ClearedMazeText = TEXT("PERFECT CLEAR");
	}
	else if (TimeCompletedPercentage < 0.5f)
	{
		ClearedMazeText = TEXT("GREAT CLEAR");
	}
	else if (TimeCompletedPercentage < 0.75f)
	{
		ClearedMazeText = TEXT("CLEAR");
	}
	else
	{
		ClearedMazeText = TEXT("SLOW CLEAR");
	}

	ClearData_Text->SetText(FText::FromString(ClearedMazeText));
}
