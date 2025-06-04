// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPD_AudioComponentBase.h"
#include "NPD_FootstepAudioComponent.generated.h"
/**
 * 
 */
UCLASS()
class NEONPULSEDARK_API UNPD_FootstepAudioComponent : public UNPD_AudioComponentBase
{
	GENERATED_BODY()

public:
	UNPD_FootstepAudioComponent();
	virtual void BeginPlay() override;
	void Footsteps(float DeltaTime);
	
	void PlayFootstepSound();



protected:
	UPROPERTY(EditAnywhere, Category = "Audio")
    TArray<USoundBase*> FootstepSounds;

	UPROPERTY(EditAnywhere, Category = "Audio")
	float FootstepInterval;
	




	//----LidarSound
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	//USoundBase* LidarSpraySound;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	//USoundBase* LidarReadySound;
private:
	float TimeSinceLastFootstep;

	int FootstepIndex;
	bool bInitialFootstep;


	int AmountOfNormalFloorSounds;
	int AmountOfDiscoFloorSounds;
	


};
