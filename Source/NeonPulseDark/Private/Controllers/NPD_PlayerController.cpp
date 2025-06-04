// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/NPD_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"
#include "Actors/Player/NPD_PlayerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "NeonPulseDark/Public/Data/Structs/UserInterfaceData.h"

ANPD_PlayerController::ANPD_PlayerController()
{
	PlayerCharacter = nullptr;
	DefaultMappingContext = nullptr;
	InputToMove = nullptr;
	InputToJump = nullptr;
	InputToLook = nullptr;
	InputToInteract = nullptr;
	InputToOpenPauseMenu = nullptr;
	MazeCompleteWidget = nullptr;
	PauseMenuWidget = nullptr;
	MazeTimerWidget = nullptr;
	LidarWidget = nullptr;
	NavToolHelpWidget = nullptr;
}


void ANPD_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PlayerCharacter = Cast<ANPD_PlayerCharacter>(InPawn);
	
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (InputLocalPlayerSubsystem)
	{
		InputLocalPlayerSubsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	BindInputMapping();
}

void ANPD_PlayerController::BindInputMapping()
{
	if (TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		if (!PlayerCharacter) return;
		EnhancedInputComponent->BindAction(InputToLook, ETriggerEvent::Triggered, PlayerCharacter, &ANPD_PlayerCharacter::Look);
		EnhancedInputComponent->BindAction(InputToMove, ETriggerEvent::Triggered, PlayerCharacter, &ANPD_PlayerCharacter::Move);
		EnhancedInputComponent->BindAction(InputToJump, ETriggerEvent::Triggered, PlayerCharacter, &ANPD_PlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(InputToInteract, ETriggerEvent::Completed, PlayerCharacter, &ANPD_PlayerCharacter::Interact);
		EnhancedInputComponent->BindAction(InputToOpenPauseMenu, ETriggerEvent::Completed, PlayerCharacter, &ANPD_PlayerCharacter::TogglePauseMode);
	}
}

void ANPD_PlayerController::OpenWidget(EUserInterfaceTypes InWidgetType, bool InCloseWidget)
{
	switch (InWidgetType)
	{
	case EUserInterfaceTypes::PauseMenu:
		{
			if (InCloseWidget && PauseMenuWidget->IsInViewport())
			{
				FInputModeGameOnly InputModeGame;
				SetShowMouseCursor(false);
				SetInputMode(InputModeGame);
				PauseMenuWidget->RemoveFromParent();
				PauseMenuOpen.Broadcast(false);
			}
			else
			{
				FInputModeGameAndUI InputMode;
				InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
				SetShowMouseCursor(true);
				SetInputMode(InputMode);
				PauseMenuOpen.Broadcast(true);
				PauseMenuWidget->AddToViewport();
			}
			break;
		}
	case EUserInterfaceTypes::MazeComplete:
		{
			if (InCloseWidget && MazeCompleteWidget->IsInViewport())
				MazeCompleteWidget->RemoveFromParent();
			else
				MazeCompleteWidget->AddToViewport();
			break;
		}
	case EUserInterfaceTypes::MazeTimer:
		{
			if (InCloseWidget && MazeTimerWidget->IsInViewport())
				MazeTimerWidget->RemoveFromParent();
			else
				MazeTimerWidget->AddToViewport();
			break;
		}
	case EUserInterfaceTypes::NavHelp:
		{
			if (InCloseWidget && NavToolHelpWidget->IsInViewport())
				NavToolHelpWidget->RemoveFromParent();
			else
				NavToolHelpWidget->AddToViewport();
			break;
		}
	default:
		break;
	}
}

bool ANPD_PlayerController::GetPauseMenuOpen()
{
	if (!PauseMenuWidget) return false;

	return PauseMenuWidget->IsInViewport();
	
}
