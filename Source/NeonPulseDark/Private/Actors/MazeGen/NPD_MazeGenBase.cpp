// Copyright (c) 2025 4ozStudio Ltd. All rights reserved.


#include "Actors/MazeGen/NPD_MazeGenBase.h"

#include "Actors/Functional/NPD_CompleteMazeDoor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Engine/PointLight.h"


ANPD_MazeGenBase::ANPD_MazeGenBase()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	WallInstancer = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Walls"));
	WallInstancer->SetupAttachment(RootComponent);
	WallInstancer->SetMobility(EComponentMobility::Static);

	FloorInstancer = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Floor"));
	FloorInstancer->SetupAttachment(RootComponent);
	FloorInstancer->SetMobility(EComponentMobility::Static);
}

void ANPD_MazeGenBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	FloorInstancer->ClearInstances();
	WallInstancer->ClearInstances();

	// Set meshes for ISMs if they haven't been set in Blueprint/Editor
	if (!FloorInstancer->GetStaticMesh() && FloorMesh)
	{
		FloorInstancer->SetStaticMesh(FloorMesh);
	}
	if (!WallInstancer->GetStaticMesh() && WallMesh)
	{
		WallInstancer->SetStaticMesh(WallMesh);
	}
	GenerateMazeLayout();
	SpawnMazeElements();
}


void ANPD_MazeGenBase::BeginPlay()
{
    Super::BeginPlay();
}

void ANPD_MazeGenBase::GenerateGrid(const int InWidth, const int InHeight)
{
	MazeWidth = FMath::Max(5, InWidth);
	MazeHeight = FMath::Max(5, InHeight);

	Grid.SetNum(MazeWidth);
	for (size_t X = 0; X < MazeWidth; ++X)
	{
		Grid[X].SetNum(MazeHeight);
		for (size_t Y = 0; Y < MazeHeight; ++Y)
		{
			Grid[X][Y] = FGridCell(X, Y);
		}
	}
}

FVector ANPD_MazeGenBase::GetCellWorldPosition(int32 InX, int32 InY) const
{
    // Center the maze around the actor's origin
    float HalfWidth = (MazeWidth * TileSize) / 2.0f;
    float HalfHeight = (MazeHeight * TileSize) / 2.0f;

    return GetActorLocation() + FVector(
        (InX * TileSize) + (TileSize / 2.0f) - HalfWidth,
        (InY * TileSize) + (TileSize / 2.0f) - HalfHeight,
        0.0f
    );
}

bool ANPD_MazeGenBase::IsValidGridCoord(int32 InX, int32 InY) const
{
    return InX >= 0 && InX < MazeWidth && InY >= 0 && InY < MazeHeight;
}