// Copyright (c) 2025 4ozStudio Ltd. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "NPD_MazeGenBase.h"
#include "NPD_MazeGenRedBlue.generated.h"

UCLASS()
class NEONPULSEDARK_API ANPD_MazeGenRedBlue : public ANPD_MazeGenBase
{
    GENERATED_BODY()

public:
    ANPD_MazeGenRedBlue();

protected:
    // Override base class generation/spawning functions
    virtual void GenerateMazeLayout() override;
    virtual void SpawnMazeElements() override;

private:
    // Generates the binary tree structure
    void GenerateBinaryDecisionTree();

    // Helper for recursive tree generation
    void BuildBinaryBranch(FIntPoint CurrentPos, int32 CurrentDepth, int32 ParentNodeIndex);

    // Spawns the physical maze elements based on generated nodes
    void SpawnBinaryDecisionMaze();

    // Parameters for binary tree generation
    UPROPERTY(EditAnywhere, Category = "BinaryTree Parameters")
    int32 MaxNodes = 10;

    UPROPERTY(EditAnywhere, Category = "BinaryTree Parameters")
    int32 MaxPathDepth = 6; // Max length of any single path from start

    UPROPERTY(EditAnywhere, Category = "BinaryTree Parameters")
    int32 MinGoalDepth = 3; // Minimum depth at which a goal node can appear

    UPROPERTY(EditAnywhere, Category = "BinaryTree Parameters")
    float DeadEndChance = 0.3f; // Chance for a branch to be a dead end, if not continuing

    UPROPERTY(EditAnywhere, Category = "BinaryTree Parameters")
    int32 MaxRetriesForPosition = 5; // How many times to try finding a new position for a node

    // Data structures for the generated maze
    UPROPERTY()
    TArray<FBinaryMazeNode> BinaryNodes;

    // Keeps track of occupied grid positions during generation to avoid overlaps
    TSet<FIntPoint> OccupiedGridPositions;

    // Directions for grid movement (North, South, East, West)
    const TArray<FIntPoint> CardinalDirections = {
        FIntPoint(0, 1),  // North (+Y)
        FIntPoint(0, -1), // South (-Y)
        FIntPoint(1, 0),  // East (+X)
        FIntPoint(-1, 0)  // West (-X)
    };
};