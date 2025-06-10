// Copyright (c) 2025 4ozStudio Ltd. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "NPD_MazeGenBase.h"
#include "NPD_MazeGenRegular.generated.h"

UCLASS()
class NEONPULSEDARK_API ANPD_MazeGenRegular : public ANPD_MazeGenBase
{
	GENERATED_BODY()
public:
	ANPD_MazeGenRegular();
protected:
	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform) override;


};
