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
	FLevelData SpaceMaze1;
	SpaceMaze1.LevelName = TEXT("/Game/Levels/Space");
	SpaceMaze1.Difficulty = ELevelDifficulty::Easy;
	SpaceMaze1.Theme = ELevelTheme::Trippy;
	SpaceMaze1.LevelType = ELevelType::Regular;
	LevelsArray.Add(SpaceMaze1);

	FLevelData Transition1;
	Transition1.LevelName = TEXT("/Game/Levels/Transition1");
	Transition1.Difficulty = ELevelDifficulty::Easy;
	Transition1.Theme = ELevelTheme::Eerie;
	Transition1.LevelType = ELevelType::Regular;
	LevelsArray.Add(Transition1);
	
	FLevelData Transition2;
	Transition2.LevelName = TEXT("/Game/Levels/Transition2");
	Transition2.Difficulty = ELevelDifficulty::Easy;
	Transition2.Theme = ELevelTheme::Ethereal;
	Transition2.LevelType = ELevelType::Regular;
	LevelsArray.Add(Transition2);
	
	FLevelData EntranceMaze1;
	EntranceMaze1.LevelName = TEXT("/Game/Levels/EntranceMaze");
	EntranceMaze1.Difficulty = ELevelDifficulty::Medium;
	EntranceMaze1.Theme = ELevelTheme::Eerie;
	EntranceMaze1.LevelType = ELevelType::Regular;
	LevelsArray.Add(EntranceMaze1);

	FLevelData LidarMaze1;
	LidarMaze1.LevelName = TEXT("/Game/Levels/LidarMaze");
	LidarMaze1.Difficulty = ELevelDifficulty::Hard;
	LidarMaze1.Theme = ELevelTheme::Trippy;
	LidarMaze1.LevelType = ELevelType::Lidar;
	LevelsArray.Add(LidarMaze1);

	FLevelData Unit9Maze;
	Unit9Maze.LevelName = TEXT("/Game/Levels/Unit9Maze");
	Unit9Maze.Difficulty = ELevelDifficulty::Hard;
	Unit9Maze.Theme = ELevelTheme::Trippy;
	Unit9Maze.LevelType = ELevelType::Epilipsy;
	LevelsArray.Add(Unit9Maze);
	
	FLevelData TrummerWeltenMaze;
	TrummerWeltenMaze.LevelName = TEXT("/Game/Levels/TrummerWelten");
	TrummerWeltenMaze.Difficulty = ELevelDifficulty::Hard;
	TrummerWeltenMaze.Theme = ELevelTheme::Sad;
	TrummerWeltenMaze.LevelType = ELevelType::Regular;
	LevelsArray.Add(TrummerWeltenMaze);
	
	FLevelData HospitalMaze;
	HospitalMaze.LevelName = TEXT("/Game/Levels/HospitalMaze");
	HospitalMaze.Difficulty = ELevelDifficulty::Hard;
	HospitalMaze.Theme = ELevelTheme::Sad;
	HospitalMaze.LevelType = ELevelType::Regular;
	LevelsArray.Add(HospitalMaze);

	FLevelData Mazuk;
	Mazuk.LevelName = TEXT("/Game/Levels/Mazuk");
	Mazuk.Difficulty = ELevelDifficulty::Hard;
	Mazuk.Theme = ELevelTheme::Trippy;
	Mazuk.LevelType = ELevelType::BlueVsRed;
	LevelsArray.Add(Mazuk);
}

void UNPD_GameInstance::SetLevelAsComplete(const FString& LevelName, const float CompletedTime)
{
	for (size_t LevelsIndex = 0; LevelsIndex < LevelsArray.Num(); LevelsIndex++)
	{
		if (LevelsArray[LevelsIndex].CompletionData.bHasComplete) continue;
		if (LevelsArray[LevelsIndex].LevelName == LevelName)
		{
			OnCompleteMaze.Broadcast();
			LevelsArray[LevelsIndex].CompletionData.bHasComplete = true;
			LevelsArray[LevelsIndex].CompletionData.TimeTaken = CompletedTime;
			PlayerData.CompletedMazeCount++;
		}
	}
}

FString UNPD_GameInstance::GetRandLevelOnConditional()
{
	TArray<FString> PotentialMazes;
	
	for (const FLevelData& Maze : LevelsArray)
	{
		if (Maze.CompletionData.bHasComplete)
			continue;

		bool bInclude = false;
		
		switch (Maze.Difficulty)
		{
		case ELevelDifficulty::Easy:
			bInclude = true;
			break;
		case ELevelDifficulty::Medium:
			bInclude = PlayerData.CompletedMazeCount > 2;
			break;
		case ELevelDifficulty::Hard:
			bInclude = PlayerData.CompletedMazeCount > 4;
			break;
		}

		if (bInclude)
		{
			if (PlayerData.BlueFlagsPickedUp > PlayerData.RedFlagsPickedUp)
			{
				if (Maze.Theme == ELevelTheme::Trippy || Maze.Theme == ELevelTheme::Ethereal)
					PotentialMazes.Add(Maze.LevelName);
			}
			else if (PlayerData.BlueFlagsPickedUp < PlayerData.RedFlagsPickedUp)
			{
				if (Maze.Theme != ELevelTheme::Ethereal)
					PotentialMazes.Add(Maze.LevelName);
			}
			else
			{
				PotentialMazes.Add(Maze.LevelName);
			}
		}
	}

	if (PotentialMazes.Num() == 0)
		return TEXT("/Game/Levels/MainMenu");
	

	const int RandomLevelIndex = FMath::RandRange(0, PotentialMazes.Num() - 1);

	return PotentialMazes[RandomLevelIndex];
}

void UNPD_GameInstance::SetCurrentLevel(const FString& InLevel)
{
	for (size_t LevelsIndex = 0; LevelsIndex < LevelsArray.Num(); LevelsIndex++)
	{
		if (LevelsArray[LevelsIndex].CompletionData.bHasComplete) continue;
		if (LevelsArray[LevelsIndex].LevelName == InLevel)
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
