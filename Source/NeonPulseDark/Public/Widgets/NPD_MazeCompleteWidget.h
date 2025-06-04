// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/NPD_WidgetBase.h"
#include "NPD_MazeCompleteWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class NEONPULSEDARK_API UNPD_MazeCompleteWidget : public UNPD_WidgetBase
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
private:
	void ProcessClearData();

protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* FadeInMazeCleared;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* FadeInClearData;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ClearData_Text;

private:
	FTimerHandle MazeCompleteTimer;
	
};
