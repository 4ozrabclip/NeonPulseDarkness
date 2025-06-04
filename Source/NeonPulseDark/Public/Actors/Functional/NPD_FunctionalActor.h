// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPD_FunctionalActor.generated.h"

class ANPD_PlayerController;
class ANPD_PlayerCharacter;
class UNPD_GameInstance;

UCLASS(Abstract)
class NEONPULSEDARK_API ANPD_FunctionalActor : public AActor
{
	GENERATED_BODY()

public:
	ANPD_FunctionalActor();
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	UNPD_GameInstance* GameInstance;
	UPROPERTY()
	ANPD_PlayerCharacter* Player;
	UPROPERTY()
	ANPD_PlayerController* PlayerController;
};
