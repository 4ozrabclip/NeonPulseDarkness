// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/NPD_PauseMenuWidget.h"

#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/Slider.h"
#include "Kismet/GameplayStatics.h"
#include "NeonPulseDark/Public/Game/NPD_GameInstance.h"

void UNPD_PauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ExitButton)
	{
		ExitButton->OnClicked.Clear();
		ExitButton->OnClicked.AddDynamic(this, &UNPD_PauseMenuWidget::OpenExitPanel);
	}
	if (ExitDefinitelyButton)
	{
		ExitDefinitelyButton->OnClicked.Clear();
		ExitDefinitelyButton->OnClicked.AddDynamic(this, &UNPD_PauseMenuWidget::ExitGame);
	}
	if (SettingsButton)
	{
		SettingsButton->OnClicked.Clear();
		SettingsButton->OnClicked.AddDynamic(this, &UNPD_PauseMenuWidget::OpenSettings);
	}
	if (BackFromSettingsButton)
	{
		BackFromSettingsButton->OnClicked.Clear();
		BackFromSettingsButton->OnClicked.AddDynamic(this, &UNPD_PauseMenuWidget::OpenPauseBase);
	}
	if (SubmitAudioVolumeSettingsButton)
	{
		SubmitAudioVolumeSettingsButton->OnClicked.Clear();
		SubmitAudioVolumeSettingsButton->OnClicked.AddDynamic(this, &UNPD_PauseMenuWidget::SubmitAudioVolumeSettings);
	}
	if (SubmitQualitySettingsButton)
	{
		SubmitQualitySettingsButton->OnClicked.Clear();
		SubmitQualitySettingsButton->OnClicked.AddDynamic(this, &UNPD_PauseMenuWidget::SubmitQualitySettings);
	}
	if (OpenAudioSettingsButton)
	{
		OpenAudioSettingsButton->OnClicked.Clear();
		OpenAudioSettingsButton->OnClicked.AddDynamic(this, &UNPD_PauseMenuWidget::OpenAudioVolumeSettings);
	}
	if (OpenQualitySettingsButton)
	{
		OpenQualitySettingsButton->OnClicked.Clear();
		OpenQualitySettingsButton->OnClicked.AddDynamic(this, &UNPD_PauseMenuWidget::OpenQualitySettings);
	}
	if (BackFromAudioVolumeSettingsButton)
	{
		BackFromAudioVolumeSettingsButton->OnClicked.Clear();
		BackFromAudioVolumeSettingsButton->OnClicked.AddDynamic(this, &UNPD_PauseMenuWidget::OpenSettings);
	}
	if (BackFromQualitySettingsButton)
	{
		BackFromQualitySettingsButton->OnClicked.Clear();
		BackFromQualitySettingsButton->OnClicked.AddDynamic(this, &UNPD_PauseMenuWidget::OpenSettings);
	}
	OpenPauseBase();
}

void UNPD_PauseMenuWidget::ExitGame()
{
	FString MainMenuLevelString = TEXT("/Game/Levels/MainMenu");
	UGameplayStatics::OpenLevel(GetWorld(), FName(MainMenuLevelString));
}

void UNPD_PauseMenuWidget::OpenPanel(UGridPanel* InPanel)
{
	// Close All Panels
	BasePauseGrid->SetVisibility(ESlateVisibility::Hidden);
	SettingsGrid->SetVisibility(ESlateVisibility::Hidden);
	AudioSettingsGrid->SetVisibility(ESlateVisibility::Hidden);
	QualitySettingsGrid->SetVisibility(ESlateVisibility::Hidden);
	AreYouSureExitGrid->SetVisibility(ESlateVisibility::Hidden);
	

	InPanel->SetVisibility(ESlateVisibility::Visible);
}


void UNPD_PauseMenuWidget::SubmitAudioVolumeSettings()
{
	if (!GameInstance)
		GameInstance = Cast<UNPD_GameInstance>(GetWorld()->GetGameInstance());

	FAudioVolumeSettings NewAudioVolumeSettings;

	NewAudioVolumeSettings.MasterVolume = MasterVolumeSlider->GetValue();
	NewAudioVolumeSettings.MusicVolume = MusicVolumeSlider->GetValue();
	NewAudioVolumeSettings.SfxVolume = SfxVolumeSlider->GetValue();

	GameInstance->UpdateAudioVolumeSettings(NewAudioVolumeSettings);
}
void UNPD_PauseMenuWidget::SubmitQualitySettings()
{
	if (!GameInstance)
		GameInstance = Cast<UNPD_GameInstance>(GetWorld()->GetGameInstance());
	
}
