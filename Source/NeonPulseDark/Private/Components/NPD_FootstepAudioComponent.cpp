// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/NPD_FootstepAudioComponent.h"
#include "Actors/Player/NPD_PlayerCharacter.h"
#include "Actors/Player/NPD_PlayerCharacter.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

UNPD_FootstepAudioComponent::UNPD_FootstepAudioComponent()
{
	AmountOfNormalFloorSounds = 4;
	AmountOfDiscoFloorSounds = 4;
	
	bInitialFootstep = false;
	FootstepIndex = 0;
	FootstepInterval = 0.65f;
	TimeSinceLastFootstep = 0.f;
	//AudioType = EAudioTypes::SfxAudio;
	Player = nullptr;

}


void UNPD_FootstepAudioComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!Player)
		Player = Cast<ANPD_PlayerCharacter>(GetOwner());
}	

void UNPD_FootstepAudioComponent::Footsteps(float DeltaTime)
{
	if (Player->GetIsWalking())
	{
		TimeSinceLastFootstep += DeltaTime;
		if (TimeSinceLastFootstep >= FootstepInterval)
		{
			PlayFootstepSound();
			TimeSinceLastFootstep = 0.f;
		}
	}
	else
	{
		TimeSinceLastFootstep = FootstepInterval;
	}
}

void UNPD_FootstepAudioComponent::PlayFootstepSound()
{
	if (FootstepSounds.Num() <= 0)
	{
		UE_LOG(LogTemp, Display, TEXT("No FootstepSounds Found"));
		return;
	}
	constexpr int MaxFootstepIndex = 3;
	if (bInitialFootstep)
	{
		if (FootstepIndex < MaxFootstepIndex)
		{
			FootstepIndex++;
		}
		else
		{
			FootstepIndex = 0;
		}
	}
	else
	{
		FootstepIndex = 0;
		bInitialFootstep = true;	
	}

	if (FootstepSounds.IsValidIndex(FootstepIndex) && FootstepSounds[FootstepIndex])
	{
		SetSound(FootstepSounds[FootstepIndex]);
		if (!IsPlaying())
		{
			Play();
		}
	}
}