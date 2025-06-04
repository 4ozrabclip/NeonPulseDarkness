// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Player/NPD_PlayerCharacter.h"

#include "Components/NPD_FootstepAudioComponent.h"
#include "Components/NPD_LidarScannerComponent.h"
#include "Components/NPD_MazeRunTrackerComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PointLightComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/Engine.h"
#include "Engine/StaticMeshActor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "Controllers/NPD_PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

ANPD_PlayerCharacter::ANPD_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	PlayerLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PlayerLight"));
	PlayerLight->SetupAttachment(RootComponent);

	LidarScanner = CreateDefaultSubobject<UNPD_LidarScannerComponent>(TEXT("Lidar Scanner"));

	MazeRunTracker = CreateDefaultSubobject<UNPD_MazeRunTrackerComponent>(TEXT("Maze Run Tracker"));
	
	FootstepAudioComponent = CreateDefaultSubobject<UNPD_FootstepAudioComponent>(TEXT("FootstepAudioComponent"));
	FootstepAudioComponent->bAutoActivate = true;
	FootstepAudioComponent->SetVolumeMultiplier(1.f);

	SpecialSoundsAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SpecialSoundsAudioComponent"));
	SpecialSoundsAudioComponent->bAutoActivate = true;
	SpecialSoundsAudioComponent->SetVolumeMultiplier(1.f);
}

void ANPD_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<ANPD_PlayerController>(GetController());
	
}
void ANPD_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateMovementState();
	
}

void ANPD_PlayerCharacter::UpdateMovementState()
{
	const FVector CurrentPosition = GetActorLocation();
	const float MovementDelta = FVector::Distance(CurrentPosition, LastPosition);
	SetIsWalking(MovementDelta > MinimumMovementThreshold);

	LastPosition = CurrentPosition;
}

FName ANPD_PlayerCharacter::GetCurrentFloorType() const
{
    FHitResult HitResult;
    FVector PlayerPosition = GetActorLocation();
    FVector GroundPosition = PlayerPosition - FVector(0.0f, 0.0f, LengthToFloor);
	
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);
	
    if (GetWorld()->LineTraceSingleByChannel(HitResult, PlayerPosition, GroundPosition, ECC_Visibility, QueryParams))
    {
        if (UPrimitiveComponent* HitComponent = HitResult.GetComponent())
        {
        	if (HitComponent->ComponentTags.Num() > 0)
        	{
        		return HitComponent->ComponentTags[0];
        	}
        }
    }
    return FName("");
}

void ANPD_PlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
	
}
void ANPD_PlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(-LookAxisVector.Y);
	
}
bool ANPD_PlayerCharacter::GetIsJumping()
{
	LengthToFloor = 100.f;
	FHitResult HitResult;
	FVector PlayerPosition = GetActorLocation();
	FVector GroundPosition = PlayerPosition - FVector(0.0f, 0.0f, LengthToFloor);
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, PlayerPosition, GroundPosition, ECC_Visibility, QueryParams))
	{
		if (HitResult.GetComponent())
		{
			return false;
		}
		return true;
	}
	return true;
}
void ANPD_PlayerCharacter::Jump()
{
	if (!GetCharacterMovement())
	{
		UE_LOG(LogTemp, Error, TEXT("Cant get character movement from Jump"));
		return;
	}
	constexpr float JumpHeight = 200.f;

	GetCharacterMovement()->JumpZVelocity = JumpHeight;
	Super::Jump();
}

void ANPD_PlayerCharacter::Interact()
{
	UE_LOG(LogTemp, Error, TEXT("Interact called"));
	switch (CurrentNavigationTool)
	{
	case ENavigationTool::None:
		UE_LOG(LogTemp, Error, TEXT("No NavTool Detected"));
		return;
	case ENavigationTool::LidarScanner:
		{
			if (LidarScanner)
			{
				UE_LOG(LogTemp, Error, TEXT("Lidar scanner detected"));
				LidarScanner->StartLidarScan();
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("No Lidar Scanner component detected"));
			}
			break;
		}
	default:
		UE_LOG(LogTemp, Error, TEXT("Default navtool????"));
		break;
	}
}

void ANPD_PlayerCharacter::TogglePauseMode()
{
	if (!PlayerController)
		PlayerController = Cast<ANPD_PlayerController>(GetController());
	
	if (PlayerController)
	{
		const bool bIsPaused = PlayerController->GetPauseMenuOpen();
		if (bIsPaused)
		{
			PlayerController->OpenWidget(EUserInterfaceTypes::PauseMenu, true);
			GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		}
		else
		{
			PlayerController->OpenWidget(EUserInterfaceTypes::PauseMenu);
			GetCharacterMovement()->SetMovementMode(MOVE_None);

		}
	}
}
