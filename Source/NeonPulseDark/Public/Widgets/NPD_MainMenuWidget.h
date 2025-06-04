// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPD_WidgetBase.h"
#include "NPD_MainMenuWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class NEONPULSEDARK_API UNPD_MainMenuWidget : public UNPD_WidgetBase
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void StartGame();
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* PlayButton;
};
