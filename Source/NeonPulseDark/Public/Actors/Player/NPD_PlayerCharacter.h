// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Character.h"
#include "NPD_PlayerCharacter.generated.h"

class UNPD_MazeRunTrackerComponent;
class UNPD_LidarScannerComponent;
class ANPD_PlayerController;
class UPointLightComponent;
class UCameraComponent;
class UNPD_FootstepAudioComponent;

UENUM()
enum class ENavigationTool
{
	None UMETA(DisplayName = "None"),
	LidarScanner UMETA(DisplayName = "Lidar Scanner")
};

UCLASS()
class NEONPULSEDARK_API ANPD_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANPD_PlayerCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;



	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	virtual void Jump() override;
	UFUNCTION()
	void Interact();
	UFUNCTION()
	void TogglePauseMode();


	bool GetIsJumping();

	//Getters and Setters
	FName GetCurrentFloorType() const;
	bool GetIsWalking() const { return bIsWalking; }
	void SetIsWalking(const bool bInIsWalking) { bIsWalking = bInIsWalking; }

	void SetCurrentNavTool(ENavigationTool InNavTool) { CurrentNavigationTool = InNavTool; }
	ENavigationTool GetCurrentNavTool() const { return CurrentNavigationTool; }
	
private: //Private Functions
	void UpdateMovementState();
	

protected: // Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPointLightComponent* PlayerLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UNPD_LidarScannerComponent* LidarScanner;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UNPD_MazeRunTrackerComponent* MazeRunTracker;

	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Components")
	UNPD_FootstepAudioComponent* FootstepAudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	UAudioComponent* SpecialSoundsAudioComponent;	


private: //Private Properties

	ENavigationTool CurrentNavigationTool;

	
	UPROPERTY()
	ANPD_PlayerController* PlayerController;
	
	UPROPERTY()
	UUserWidget* CreatedWidget;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	float MinimumMovementThreshold = 0.5f;
	  
	float LengthToFloor = 100.f;
	float PlayerMovementSpeed;


	FVector LastPosition;
	
	bool bCanMove;
	bool bIsWalking;
	bool bIsStairs;







};
