// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NeonPulseDark/Public/Data/Structs/UserInterfaceData.h"
#include "NPD_PlayerController.generated.h"

class ANPD_PlayerCharacter;
class UInputAction;
class UInputMappingContext;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPauseMenuOpen, bool, bIsOpen);
/**
 * 
 */
UCLASS()
class NEONPULSEDARK_API ANPD_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ANPD_PlayerController();
	virtual void OnPossess(APawn* InPawn) override;
	
	void BindInputMapping();
	
	void OpenWidget(EUserInterfaceTypes InWidgetType, bool InCloseWidget = false);


	bool GetPauseMenuOpen();

	UPROPERTY(BlueprintReadWrite, Category = Events)
	FPauseMenuOpen PauseMenuOpen;

protected: // Enhanced input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* InputToMove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* InputToLook;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* InputToJump;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* InputToInteract;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* InputToOpenPauseMenu;


	// Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
	UUserWidget* MazeCompleteWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
	UUserWidget* PauseMenuWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
	UUserWidget* MazeTimerWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
	UUserWidget* LidarWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
	UUserWidget* NavToolHelpWidget;


private:
	UPROPERTY()
	ANPD_PlayerCharacter* PlayerCharacter;
	
};
