// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPD_WidgetBase.h"
#include "NPD_PauseMenuWidget.generated.h"

class USlider;
class UGridPanel;
class UButton;
/**
 * 
 */
UCLASS()
class NEONPULSEDARK_API UNPD_PauseMenuWidget : public UNPD_WidgetBase
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ExitGame();
	UFUNCTION()
	void OpenSettings() { OpenPanel(SettingsGrid); }
	UFUNCTION()
	void OpenAudioVolumeSettings() { OpenPanel(AudioSettingsGrid); }
	UFUNCTION()
	void OpenQualitySettings() { OpenPanel(QualitySettingsGrid); }
	UFUNCTION()
	void OpenPauseBase() { OpenPanel(BasePauseGrid); }
	UFUNCTION()
	void OpenExitPanel() { OpenPanel(AreYouSureExitGrid); }
	UFUNCTION()
	void SubmitAudioVolumeSettings();
	UFUNCTION()
	void SubmitQualitySettings();

	void OpenPanel(UGridPanel* InPanel);

protected:
	
	UPROPERTY(meta = (BindWidget))
	UGridPanel* BasePauseGrid;
	UPROPERTY(meta = (BindWidget))
	UGridPanel* SettingsGrid;
	UPROPERTY(meta = (BindWidget))
	UGridPanel* AudioSettingsGrid;
	UPROPERTY(meta = (BindWidget))
	UGridPanel* QualitySettingsGrid;
	UPROPERTY(meta = (BindWidget))
	UGridPanel* AreYouSureExitGrid;

	
	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ExitDefinitelyButton;
	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* BackFromSettingsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* BackFromAudioVolumeSettingsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* BackFromQualitySettingsButton;
	


	// Settings
	UPROPERTY(meta = (BindWidget))
	USlider* MasterVolumeSlider;
	UPROPERTY(meta = (BindWidget))
	USlider* MusicVolumeSlider;
	UPROPERTY(meta = (BindWidget))
	USlider* SfxVolumeSlider;
	UPROPERTY(meta = (BindWidget))
	UButton* OpenQualitySettingsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* OpenAudioSettingsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* SubmitAudioVolumeSettingsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* SubmitQualitySettingsButton;
};
