// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Functional/MusicPlayer.h"
#include "Components/AudioComponent.h"
#include "TimerManager.h"
#include "Components/NPD_AudioComponentBase.h"

// Sets default values
AMusicPlayer::AMusicPlayer()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	AudioComponent = CreateDefaultSubobject<UNPD_AudioComponentBase>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	
	CurrentSongIndex = 0;
}

void AMusicPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (!AudioComponent) return;
	
	AudioComponent->SetAudioType(EAudioType::Music);
	
	AudioComponent->OnAudioFinished.Clear();
	AudioComponent->OnAudioFinished.AddDynamic(this, &AMusicPlayer::PlayNextSong);

	if (bPlayOnStart)
		PlayNextSong();
}

void AMusicPlayer::PlayNextSong()
{
	AudioComponent->SetSound(Songs[CurrentSongIndex]);
	AudioComponent->Play();

	CurrentSongIndex = (CurrentSongIndex + 1) % Songs.Num();
}

void AMusicPlayer::PlaySongAtIndex(const int Index)
{
	if (Songs.IsValidIndex(Index))
	{
		AudioComponent->SetSound(Songs[Index]);
		AudioComponent->Play();
		CurrentSongIndex = Index;
	}
}

void AMusicPlayer::FadeOut(float FadeOutTime)
{
	if (AudioComponent && AudioComponent->IsPlaying())
	{
		CurrentVolume = AudioComponent->VolumeMultiplier;

		TargetVolume = 0.0f;

		MusicFadeDelegate.BindLambda([this, FadeOutTime]()
			{
				for (int VolumeLevel = 0; VolumeLevel < 300; ++VolumeLevel)
				{
					float NewVolume = FMath::Lerp(CurrentVolume, TargetVolume, VolumeLevel / 300.0f);
					AudioComponent->SetVolumeMultiplier(NewVolume);
					//FPlatformProcess::Sleep(FadeOutTime / 300.0f); 
				}
			});
		GetWorld()->GetTimerManager().SetTimer(FadeOutTimerHandle, MusicFadeDelegate, FadeOutTime, false);
	}
}