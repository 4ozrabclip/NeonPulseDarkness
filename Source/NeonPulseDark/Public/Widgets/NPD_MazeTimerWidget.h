// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPD_WidgetBase.h"
#include "NPD_MazeTimerWidget.generated.h"

class UNPD_MazeRunTrackerComponent;
class UProgressBar;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCountdownFinished);
UCLASS()
class NEONPULSEDARK_API UNPD_MazeTimerWidget : public UNPD_WidgetBase
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry & MyGeometry, float InDeltaTime) override;

	void InitializeCountdown();
	void CountdownFinished();
	UFUNCTION()
	void CompleteMaze() { SetIsNotActive(true); }

	UFUNCTION()
	void SetIsNotActive(bool InIsNotActive) { bIsNotActive = InIsNotActive; }

	UFUNCTION()
	void ResetTimer();
	

	UPROPERTY(BlueprintReadOnly, Category = Events)
	FOnCountdownFinished OnCountdownFinished;
/*private:
	UPROPERTY()
	UNPD_MazeRunTrackerComponent* MazeRunTracker;*/
protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* CountdownBar;

private:
	bool bIsNotActive = true;

	float CurrentTime = 0.f;
	float MaxTime = 280.f;
	
};
