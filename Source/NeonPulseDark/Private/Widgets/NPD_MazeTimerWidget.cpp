// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/NPD_MazeTimerWidget.h"

#include "Components/NPD_MazeRunTrackerComponent.h"
#include "Actors/Player/NPD_PlayerCharacter.h"
#include "Components/ProgressBar.h"
#include "Controllers/NPD_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "NeonPulseDark/Public/Game/NPD_GameInstance.h"

void UNPD_MazeTimerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsNotActive(true);
	
	InitializeCountdown();

	if (ANPD_PlayerController* PlayerController = Cast<ANPD_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		PlayerController->PauseMenuOpen.AddDynamic(this, &UNPD_MazeTimerWidget::SetIsNotActive);
	}

	if (!GameInstance)
		GameInstance = Cast<UNPD_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance)
	{
		GameInstance->OnCompleteMaze.AddDynamic(this, &UNPD_MazeTimerWidget::ResetTimer);
	}

	if (!Player)
		Player = Cast<ANPD_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	
	
}

void UNPD_MazeTimerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (bIsNotActive) return;
	
	if (CurrentTime > 0.f)
	{
		CurrentTime -= InDeltaTime;

		float ClampedPercent = FMath::Clamp(CurrentTime / MaxTime, 0.f, 1.f);

		CountdownBar->SetPercent(ClampedPercent);
		
		if (CurrentTime <= 0.f)
		{
			CountdownFinished();
			SetIsNotActive(true);
		}
	}
}

void UNPD_MazeTimerWidget::InitializeCountdown()
{
	CountdownBar->SetPercent(1.f);
	if (!GameInstance)
		GameInstance = Cast<UNPD_GameInstance>(GetWorld()->GetGameInstance());

	FLevelData CurrentLevel = GameInstance->GetCurrentLevelData();

	MaxTime = CurrentLevel.GetTimeLimit();
	
	CurrentTime = MaxTime;
	
	SetIsNotActive(false);
}
void UNPD_MazeTimerWidget::ResetTimer()
{
	CountdownBar->SetPercent(1.f);
}

void UNPD_MazeTimerWidget::CountdownFinished()
{
	
}

