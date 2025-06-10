// Copyright (c) 2025 4ozStudio Ltd. All rights reserved.


#include "Actors/MazeGen/NPD_MazeGenRedBlue.h"
#include "Kismet/GameplayStatics.h" // For UGameplayStatics::SpawnActor, if needed for markers
#include "DrawDebugHelpers.h" // For debugging visualization
#include "Actors/Functional/NPD_CompleteMazeDoor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Engine/PointLight.h"

ANPD_MazeGenRedBlue::ANPD_MazeGenRedBlue()
{
}

void ANPD_MazeGenRedBlue::GenerateMazeLayout()
{
    GenerateBinaryDecisionTree();
}

void ANPD_MazeGenRedBlue::SpawnMazeElements()
{
    SpawnBinaryDecisionMaze();
}

void ANPD_MazeGenRedBlue::GenerateBinaryDecisionTree()
{

}

void ANPD_MazeGenRedBlue::BuildBinaryBranch(FIntPoint CurrentPos, int32 CurrentDepth, int32 ParentNodeIndex)
{
}

void ANPD_MazeGenRedBlue::SpawnBinaryDecisionMaze()
{
}