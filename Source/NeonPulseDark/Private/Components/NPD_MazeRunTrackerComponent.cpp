// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/NPD_MazeRunTrackerComponent.h"

#include "Controllers/NPD_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "NeonPulseDark/Public/Game/NPD_GameInstance.h"
#include "NeonPulseDark/Public/Data/Structs/LevelData.h"
#include "NeonPulseDark/Public/Data/Structs/UserInterfaceData.h"


UNPD_MazeRunTrackerComponent::UNPD_MazeRunTrackerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNPD_MazeRunTrackerComponent::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(false);

	InitializeCountdown();

	if (!PlayerController)
		PlayerController = Cast<ANPD_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PlayerController)
	{
		PlayerController->PauseMenuOpen.AddDynamic(this, &UNPD_MazeRunTrackerComponent::SetIsNotActive);
		
	}

	if (!GameInstance)
		GameInstance = Cast<UNPD_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance)
	{
		GameInstance->OnCompleteMaze.AddDynamic(this, &UNPD_MazeRunTrackerComponent::OnCompleteMaze);
	}
}

void UNPD_MazeRunTrackerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                 FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (bIsNotActive) return;
	
	if (CurrentTime > 0.f)
	{
		CurrentTime -= DeltaTime;
		
		if (CurrentTime <= 0.f)
		{
			SetIsNotActive(true);
		}
	}
}
void UNPD_MazeRunTrackerComponent::InitializeCountdown()
{
	if (!GameInstance)
		GameInstance = Cast<UNPD_GameInstance>(GetWorld()->GetGameInstance());

	FLevelData CurrentLevel = GameInstance->GetCurrentLevelData();

	MaxTime = CurrentLevel.GetTimeLimit();
	
	CurrentTime = MaxTime;

	if (PlayerController)
		PlayerController->OpenWidget(EUserInterfaceTypes::MazeTimer);
	SetComponentTickEnabled(true);
}

void UNPD_MazeRunTrackerComponent::OnCompleteMaze()
{
	SetIsNotActive(true);
	
}
