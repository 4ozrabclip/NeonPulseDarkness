#pragma once
#include "CoreMinimal.h"
#include "PlayerData.generated.h"


USTRUCT()
struct FPlayerData
{
	GENERATED_USTRUCT_BODY()
	FPlayerData() :
	RedFlagsPickedUp(0),
	BlueFlagsPickedUp(0),
	CompletedMazeCount(0)
	{}
	
	int RedFlagsPickedUp;
	int BlueFlagsPickedUp;

	int CompletedMazeCount;
	
};
