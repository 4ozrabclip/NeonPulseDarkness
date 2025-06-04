// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NPD_PlayerComponentBase.generated.h"


class ANPD_PlayerController;
class UNPD_GameInstance;
class ANPD_PlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Abstract )
class NEONPULSEDARK_API UNPD_PlayerComponentBase : public UActorComponent
{
	GENERATED_BODY()
public:	
	UNPD_PlayerComponentBase();
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	ANPD_PlayerCharacter* Player;
	UPROPERTY()
	ANPD_PlayerController* PlayerController;
	UPROPERTY()
	UNPD_GameInstance* GameInstance;
	
};
