// Copyright (c) 2025 4ozStudio Ltd. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/Structs/LevelData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "NPD_MusicPlayerSubsystem.generated.h"

class UNPD_AudioComponentBase;
class UNPD_GameInstance;
/**
 * 
 */
UCLASS()
class NEONPULSEDARK_API UNPD_MusicPlayerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UNPD_MusicPlayerSubsystem();
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	UFUNCTION()
	void PlayNextSong();


private:
	UPROPERTY(VisibleAnywhere)
	UNPD_AudioComponentBase* AudioComponent;

	UPROPERTY()
	UNPD_GameInstance* GameInstance;

	int CurrentSongIndex;
};

