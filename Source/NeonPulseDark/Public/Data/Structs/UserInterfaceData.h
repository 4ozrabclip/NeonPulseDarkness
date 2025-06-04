#pragma once

#include "CoreMinimal.h"
#include "UserInterfaceData.generated.h"
/**
 * 
 */
UENUM(Blueprintable)
enum class EUserInterfaceTypes : uint8
{
	PauseMenu		UMETA(DisplayName = "PauseMenu"),
	MazeComplete	UMETA(DisplayName = "MazeComplete"),
	MazeTimer		UMETA(DisplayName = "MazeTimer"),
	NavHelp			UMETA(DisplayName = "NavHelp")
};
