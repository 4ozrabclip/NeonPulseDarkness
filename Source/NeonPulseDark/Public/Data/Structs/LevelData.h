#pragma once
#include "CoreMinimal.h"
#include "LevelData.generated.h"

UENUM()
enum class ELevelFlagType : uint8
{
	RedFlag = 0,
	BlueFlag = 1
};
UENUM()
enum class ELevelDifficulty : uint8
{
	Easy UMETA(DisplayName = "Easy Difficulty"),
	Medium UMETA(DisplayName = "Medium Difficulty"),
	Hard UMETA(DisplayName = "Hard Difficulty")
};

UENUM()
enum class ELevelType
{
	Regular		UMETA(DisplayName = "Regular Level"),
	BlueVsRed	UMETA(DisplayName = "Blue Vs Red Level"),
	Lidar		UMETA(DisplayName = "Lidar Level"),
	Epilipsy	UMETA(DisplayName = "Epilipsy Level"),
};

UENUM()
enum class ELevelTheme : uint8
{
	Scary UMETA(DisplayName = "Scary"),
	Eerie UMETA(DisplayName = "Eerie"),
	Sad UMETA(DisplayName = "Sad"),
	Ethereal UMETA(DisplayName = "Ethereal"),
	Trippy UMETA(DisplayName = "Trippy")
};

USTRUCT()
struct FLevelCompletionData
{
	GENERATED_USTRUCT_BODY()

	FLevelCompletionData() :
	bHasComplete(false),
	TimeTaken(0.f)
	{}
	
	UPROPERTY()
	bool bHasComplete;

	UPROPERTY()
	float TimeTaken;
	
};

USTRUCT(Blueprintable)
struct FLevelData
{
	GENERATED_USTRUCT_BODY()

	FLevelData() :
	LevelName(""),
	Difficulty(ELevelDifficulty::Medium),
	Theme(ELevelTheme::Eerie),
	LevelType(ELevelType::Regular)
	{}

	UPROPERTY(EditAnywhere)
	FString LevelName;

	UPROPERTY(EditAnywhere)
	ELevelDifficulty Difficulty;

	UPROPERTY(EditAnywhere)
	ELevelTheme Theme;

	UPROPERTY()
	FLevelCompletionData CompletionData;

	UPROPERTY(EditAnywhere)
	ELevelType LevelType;

	float GetTimeLimit() const
	{
		switch (Difficulty)
		{
		case ELevelDifficulty::Easy: return 280.f;
		case ELevelDifficulty::Medium: return 350.f;
		case ELevelDifficulty::Hard: return 390.f;
		default: return 280.f;
		}
	}
	
};

