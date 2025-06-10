// Copyright (c) 2025 4ozStudio Ltd. All rights reserved.


#include "Game/NPD_MusicPlayerSubsystem.h"

#include "Components/AudioComponent.h"
#include "Components/NPD_AudioComponentBase.h"
#include "Game/NPD_GameInstance.h"

UNPD_MusicPlayerSubsystem::UNPD_MusicPlayerSubsystem()
{
	AudioComponent = nullptr;
	GameInstance = nullptr;
	CurrentSongIndex = 0;
}

void UNPD_MusicPlayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (UWorld* World = GetWorld())
	{
		GameInstance = Cast<UNPD_GameInstance>(World->GetGameInstance());
		
		AudioComponent = NewObject<UNPD_AudioComponentBase>(World);
		if (!AudioComponent) return;
		AudioComponent->RegisterComponentWithWorld(World);
		AudioComponent->bAutoActivate = false;
		
		AudioComponent->AddToRoot();
		AudioComponent->SetAudioType(EAudioType::Music);

		AudioComponent->OnAudioFinished.AddDynamic(this, &UNPD_MusicPlayerSubsystem::PlayNextSong);
	}
}
void UNPD_MusicPlayerSubsystem::Deinitialize()
{
	if (AudioComponent)
	{
		AudioComponent->Stop();
		AudioComponent->OnAudioFinished.Clear();
		AudioComponent->RemoveFromRoot();
	}
	Super::Deinitialize();
}

void UNPD_MusicPlayerSubsystem::PlayNextSong()
{
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("No Game Instance in MusicPlayerSubsystem when trying to play next song"));
		return;
	}
	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("AudioComponent is null in PlayNextSong"));
		return;
	}
	FGameMoodData& MoodData = GameInstance->GetCurrentGameMood();
	TArray<USoundBase*>& CurrentMoodSongs = MoodData.Songs;
	
	if ( CurrentMoodSongs.Num() < 2) return;

	int TempSongIndex;
	do
	{
		TempSongIndex = FMath::RandRange(0, CurrentMoodSongs.Num() - 1);
	}while (TempSongIndex == CurrentSongIndex);

	CurrentSongIndex = TempSongIndex;
	
	if (CurrentMoodSongs.IsValidIndex(CurrentSongIndex))
	{
		AudioComponent->SetSound(CurrentMoodSongs[CurrentSongIndex]);
		AudioComponent->Play();

	}
}
