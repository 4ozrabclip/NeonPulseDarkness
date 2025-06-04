// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Data/Structs/GameSettings.h"
#include "Data/Structs/LevelData.h"
#include "Data/Structs/PlayerData.h"
#include "NPD_GameInstance.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudioVolumeSettingsChanged, FAudioVolumeSettings, InAudioVolumeSettings);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCompleteMaze);
UCLASS()
class NEONPULSEDARK_API UNPD_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UNPD_GameInstance();
	virtual void Init() override;
	void InitializeLevelsArray();
	void SetLevelAsComplete(const FString& LevelName, const float CompletedTime);
	FString GetRandLevelOnConditional();

	void SetCurrentLevel(const FString& InLevel);
	void AddLevelFlagToPlayerData(ELevelFlagType InFlag);
	FLevelData GetCurrentLevelData() { return CurrentLevel; }
	FPlayerData GetPlayerData() const { return PlayerData; }
	FGameSettings GetGameSettings() const { return GameSettings; }

	UFUNCTION()
	void UpdateAudioVolumeSettings(const FAudioVolumeSettings InAudioVolumeSettings);


	

	//Delegate events
	UPROPERTY(BlueprintReadWrite, Category = Events)
	FOnCompleteMaze OnCompleteMaze;
	UPROPERTY(BlueprintReadWrite, Category = Events)
	FOnAudioVolumeSettingsChanged OnAudioVolumeSettingsChanged;
protected:
	UPROPERTY(EditAnywhere, Category = "Levels")
	TArray<FLevelData> LevelsArray;

	FPlayerData PlayerData;

	FGameSettings GameSettings;

private:
	FLevelData CurrentLevel;
	
};
