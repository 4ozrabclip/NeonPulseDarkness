// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/NPD_MainMenuWidget.h"

#include "Components/Button.h"
#include "Game/NPD_GameInstance.h"
#include "Kismet/GameplayStatics.h"

void UNPD_MainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (PlayButton)
	{
		PlayButton->OnClicked.Clear();
		PlayButton->OnClicked.AddDynamic(this, &UNPD_MainMenuWidget::StartGame);
	}
}

void UNPD_MainMenuWidget::StartGame()
{
	if (!GameInstance)
		GameInstance = Cast<UNPD_GameInstance>(GetWorld()->GetGameInstance());
	
	if (GameInstance)
	{
		FName StartLevel = FName(GameInstance->GetRandLevelOnConditional());
		UGameplayStatics::OpenLevel(GetWorld(), StartLevel);
	}


}
