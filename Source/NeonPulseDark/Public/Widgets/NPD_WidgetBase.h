// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPD_WidgetBase.generated.h"

class UNPD_GameInstance;
class ANPD_PlayerCharacter;
/**
 * 
 */
UCLASS(Abstract)
class NEONPULSEDARK_API UNPD_WidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	ANPD_PlayerCharacter* Player;

	UPROPERTY()
	UNPD_GameInstance* GameInstance;
	
};
