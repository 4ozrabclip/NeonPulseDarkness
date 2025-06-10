#pragma once
#include "CoreMinimal.h"
#include "MazeGenData.generated.h"
UENUM()
enum class EMazeAlgo
{
	DepthFirstSearch	UMETA(DisplayName = "Depth First Search"),
	BinaryDecision		UMETA(DisplayName = "Binary Decision"),
};
UENUM()
enum class EMazePathType
{
	Continue		UMETA(DisplayName = "Continue"),
	GoBack			UMETA(DisplayName = "Go Back"),
	DeadEnd			UMETA(DisplayName = "Dead End")
};
USTRUCT()
struct FBinaryDecisionBranch
{
	GENERATED_USTRUCT_BODY()

	FBinaryDecisionBranch() :
	PathType(EMazePathType::DeadEnd),
	TargetNodeIndex(INDEX_NONE)
	{}
	
	UPROPERTY()
	EMazePathType PathType;

	UPROPERTY()
	int TargetNodeIndex;
};
USTRUCT()
struct FBinaryMazeNode
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY()
	FBinaryDecisionBranch RedBranch;
	UPROPERTY()
	FBinaryDecisionBranch BlueBranch;

	UPROPERTY()
	bool bIsGoalNode = false;

	UPROPERTY()
	FIntPoint GridPosition;
	
};
USTRUCT()
struct FGridCell
{
	GENERATED_USTRUCT_BODY()
	FGridCell() :
		Position(FIntPoint::ZeroValue),
		bVisited(false)
	{}

	FGridCell(int InX, int InY) :
		Position(InX, InY),
		bVisited(false)
	{}
	UPROPERTY()
	FIntPoint Position;

	UPROPERTY()
	bool bVisited;

};
