// Fill out your copyright notice in the Description page of Project Settings.


#include "NeonPulseDark/Public/Game/NPD_GameInstance.h"

UNPD_GameInstance::UNPD_GameInstance()
{
}

void UNPD_GameInstance::Init()
{
	Super::Init();

	//InitializeLevelsArray();
	
}
void UNPD_GameInstance::InitializeLevelsArray()
{
	FLevelData RegularMaze1;
	RegularMaze1.LevelPath = TEXT("/Game/Levels/Regular");
	RegularMaze1.LevelType = ELevelType::Regular;
	RegularMaze1.PointsScored = 0;
	LevelsArray.Add(RegularMaze1);

	FLevelData RedVsBlueMaze;
	RedVsBlueMaze.LevelPath = TEXT("/Game/Levels/RedVsBlue");
	RedVsBlueMaze.LevelType = ELevelType::RedVsBlue;
	RedVsBlueMaze.PointsScored = 0;
	LevelsArray.Add(RedVsBlueMaze);

}

void UNPD_GameInstance::SetLevelAsComplete(const FString& LevelPath, const float CompletedTime)
{
	for (size_t LevelsIndex = 0; LevelsIndex < LevelsArray.Num(); LevelsIndex++)
	{
		if (LevelsArray[LevelsIndex].LevelPath == LevelPath)
		{
			OnCompleteMaze.Broadcast();
			LevelsArray[LevelsIndex].PointsScored++;
			PlayerData.CompletedMazeCount++;
			break;
		}
	}
}

FString UNPD_GameInstance::GetRandLevelOnConditional()
{
	int RandomMazeIndex = FMath::RandRange(0, LevelsArray.Num() - 1);

	if (LevelsArray.IsValidIndex(RandomMazeIndex))
		return LevelsArray[RandomMazeIndex].LevelPath;
	else
		return TEXT("Game/Levels/MainMenu");
}

void UNPD_GameInstance::SetCurrentLevel(const FString& InLevel)
{
	for (size_t LevelsIndex = 0; LevelsIndex < LevelsArray.Num(); LevelsIndex++)
	{
		if (LevelsArray[LevelsIndex].LevelPath == InLevel)
			CurrentLevel = LevelsArray[LevelsIndex];
	}
}
void UNPD_GameInstance::AddLevelFlagToPlayerData(const ELevelFlagType InFlag)
{
	switch (InFlag)
	{
	case ELevelFlagType::RedFlag:
		PlayerData.RedFlagsPickedUp++;
		break;
	case ELevelFlagType::BlueFlag:
		PlayerData.BlueFlagsPickedUp++;
		break;
	default:
		break;
	}
}

void UNPD_GameInstance::UpdateAudioVolumeSettings(const FAudioVolumeSettings InAudioVolumeSettings)
{
	GameSettings.AudioVolumeSettings = InAudioVolumeSettings;

	OnAudioVolumeSettingsChanged.Broadcast(GameSettings.AudioVolumeSettings);
}
