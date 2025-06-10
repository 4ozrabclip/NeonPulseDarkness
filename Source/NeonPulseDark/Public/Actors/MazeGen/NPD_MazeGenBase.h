// Copyright (c) 2025 4ozStudio Ltd. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/Structs/MazeGenData.h"
#include "GameFramework/Actor.h"
#include "NPD_MazeGenBase.generated.h"

class ANPD_CompleteMazeDoor; // Forward declaration
class APointLight;           // Forward declaration

UCLASS(Abstract) // Make this class abstract as it's meant to be inherited
class NEONPULSEDARK_API ANPD_MazeGenBase : public AActor
{
    GENERATED_BODY()

public:
    ANPD_MazeGenBase();

protected:
    virtual void OnConstruction(const FTransform& Transform) override;
    virtual void BeginPlay() override;
    
    virtual void GenerateMazeLayout() PURE_VIRTUAL(ANPD_MazeGenBase::GenerateMazeLayout, );
    virtual void SpawnMazeElements() PURE_VIRTUAL(ANPD_MazeGenBase::SpawnMazeElements, );


    void GenerateGrid(const int InWidth, const int InHeight);
    
    FVector GetCellWorldPosition(int InX, int InY) const;
    bool IsValidGridCoord(int InX, int InY) const;

    
    //Regular Properties
    TArray<TArray<FGridCell>> Grid;
    
protected: // UPROPERTYS
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze Dimensions")
    int MazeWidth = 10;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze Dimensions")
    int MazeHeight = 10;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze Dimensions")
    float TileSize = 400.f;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UInstancedStaticMeshComponent* FloorInstancer;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UInstancedStaticMeshComponent* WallInstancer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
    UStaticMesh* FloorMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
    UStaticMesh* WallMesh;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze Markers")
    TSubclassOf<APointLight> EntranceMarkerClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze Markers")
    TSubclassOf<ANPD_CompleteMazeDoor> CompleteMazeDoorClass;

    
};