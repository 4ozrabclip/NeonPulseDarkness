// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/NPD_AudioComponentBase.h"

#include "Actors/Player/NPD_PlayerCharacter.h"
#include "NeonPulseDark/Public/Game/NPD_GameInstance.h"

UNPD_AudioComponentBase::UNPD_AudioComponentBase()
{
	Player = nullptr;
	AudioType = EAudioType::Music;
}

void UNPD_AudioComponentBase::BeginPlay()
{
	Super::BeginPlay();

	if (!Player)
		Player = Cast<ANPD_PlayerCharacter>(GetOwner());

	if (UNPD_GameInstance* GameInstance = Cast<UNPD_GameInstance>(GetWorld()->GetGameInstance()))
	{
		GameInstance->OnAudioVolumeSettingsChanged.AddDynamic(this, &UNPD_AudioComponentBase::UpdateVolumeSettings);
	}
}

void UNPD_AudioComponentBase::UpdateVolumeSettings(FAudioVolumeSettings InAudioVolumeSettings)
{
	if (AudioType == EAudioType::Music)
	{
		SetVolumeMultiplier(InAudioVolumeSettings.MusicVolume * InAudioVolumeSettings.MasterVolume);
	}
	else if (AudioType == EAudioType::Sfx)
	{
		SetVolumeMultiplier(InAudioVolumeSettings.SfxVolume * InAudioVolumeSettings.MasterVolume);
	}
}
