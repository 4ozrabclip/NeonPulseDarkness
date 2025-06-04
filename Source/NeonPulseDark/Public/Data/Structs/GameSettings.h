#pragma once
#include "CoreMinimal.h"
#include "GameSettings.generated.h"

UENUM()
enum class EAudioType
{
	Music	UMETA(DisplayName = "Music"),
	Sfx		UMETA(DisplayName = "Sfx")
};

USTRUCT(BlueprintType)
struct FAudioVolumeSettings
{
	GENERATED_USTRUCT_BODY()

	FAudioVolumeSettings() :
	MasterVolume(1.f),
	SfxVolume(1.f),
	MusicVolume(1.f)
	{}
	
	UPROPERTY()
	float MasterVolume;
	UPROPERTY()
	float SfxVolume;
	UPROPERTY()
	float MusicVolume;
};
/*USTRUCT()
struct FQualitySettings
{
	GENERATED_USTRUCT_BODY()

};*/
USTRUCT(BlueprintType)
struct FGameSettings
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY()
	FAudioVolumeSettings AudioVolumeSettings;
	//FQualitySettings QualitySettings;
};