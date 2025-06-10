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
	RedVsBlue	UMETA(DisplayName = "Red Vs Blue Level"),
	Lidar		UMETA(DisplayName = "Lidar Level"),
	Epilipsy	UMETA(DisplayName = "Epilipsy Level"),
};

UENUM()
enum class EGameMood
{
	Scary UMETA(DisplayName = "Scary"),
	Eerie UMETA(DisplayName = "Eerie"),
	Sad UMETA(DisplayName = "Sad"),
	Ethereal UMETA(DisplayName = "Ethereal"),
	Trippy UMETA(DisplayName = "Trippy")
};

USTRUCT(BlueprintType)
struct FGameMoodData
{
	GENERATED_USTRUCT_BODY()
	FGameMoodData() :
	Mood(EGameMood::Eerie)
	{}
	
	UPROPERTY(BlueprintReadOnly, Category = "Mood Type")
	EGameMood Mood;
	
	UPROPERTY(EditAnywhere)
	TArray<USoundBase*> Songs;
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
	LevelPath(""),
	LevelType(ELevelType::Regular),
	PointsScored(0)
	{}

	UPROPERTY(EditAnywhere)
	FString LevelPath;

	UPROPERTY(EditAnywhere)
	ELevelType LevelType;
	
	UPROPERTY()
	int PointsScored;
	
};
