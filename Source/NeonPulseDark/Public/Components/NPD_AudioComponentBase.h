// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "NeonPulseDark/Public/Data/Structs/GameSettings.h"
#include "NPD_AudioComponentBase.generated.h"

class ANPD_PlayerCharacter;
/**
 * 
 */

UCLASS()
class NEONPULSEDARK_API UNPD_AudioComponentBase : public UAudioComponent
{
	GENERATED_BODY()
public:
	UNPD_AudioComponentBase();
protected:
	virtual void BeginPlay() override;
public:
	UFUNCTION()
	void SetAudioType(const EAudioType InAudioType) { AudioType = InAudioType; }

	UFUNCTION()
	void UpdateVolumeSettings(FAudioVolumeSettings InAudioVolumeSettings);

	

protected:
	UPROPERTY(BlueprintReadOnly)
	EAudioType AudioType;
	
protected:
	UPROPERTY()
	ANPD_PlayerCharacter* Player;
};
