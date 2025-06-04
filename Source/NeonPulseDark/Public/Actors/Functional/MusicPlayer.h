// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MusicPlayer.generated.h"

class UNPD_AudioComponentBase;

UCLASS(Blueprintable)
class NEONPULSEDARK_API AMusicPlayer : public AActor
{
	GENERATED_BODY()
public:	
	AMusicPlayer();
protected:
	virtual void BeginPlay() override;
public:
	UFUNCTION(BlueprintCallable, Category = "Music")
	void PlayNextSong();
	UFUNCTION(BlueprintCallable, Category = "Music")
	void PlaySongAtIndex(int Index);

	UFUNCTION(BlueprintCallable, Category = "Music")
	void FadeOut(float FadeOutTime);

	UFUNCTION(BlueprintCallable)
	void SetPlayOnStart(const bool bInPlayOnStart) { bPlayOnStart = bInPlayOnStart; }

protected: // components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	UNPD_AudioComponentBase* AudioComponent;

	// UPROPERTY
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Play On Start")
	bool bPlayOnStart = true;


private:
	UPROPERTY(EditAnywhere, Category = "Music")
	TArray<USoundWave*> Songs;
	FTimerHandle FadeOutTimerHandle;
	
	int CurrentSongIndex;
	float CurrentVolume;
	UPROPERTY(EditAnywhere, Category =  "Audio")
	float MaxVolume = 2.f;
	float TargetVolume;
	FTimerDelegate MusicFadeDelegate;


};