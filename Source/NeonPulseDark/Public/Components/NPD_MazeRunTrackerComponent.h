// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPD_PlayerComponentBase.h"
#include "NPD_MazeRunTrackerComponent.generated.h"


class ANPD_PlayerController;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEONPULSEDARK_API UNPD_MazeRunTrackerComponent : public UNPD_PlayerComponentBase
{
	GENERATED_BODY()
public:
	UNPD_MazeRunTrackerComponent();
protected:
	virtual void BeginPlay() override;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	void InitializeCountdown();
	
	float GetCurrentTime() const { return CurrentTime; }
	float GetMaxTime() const { return MaxTime; }
	
	UFUNCTION()
	void SetIsNotActive(bool InIsNotActive) { bIsNotActive = InIsNotActive; }

	UFUNCTION()
	void OnCompleteMaze();
	

private:
	float MaxTime = 0.f;
	float CurrentTime = 0.f;
	

	bool bIsNotActive = false;
};
