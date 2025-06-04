// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/NPD_PlayerComponentBase.h"

#include "Actors/Player/NPD_PlayerCharacter.h"
#include "Controllers/NPD_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "NeonPulseDark/Public/Game/NPD_GameInstance.h"

UNPD_PlayerComponentBase::UNPD_PlayerComponentBase()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	GameInstance = nullptr;
	Player = nullptr;
	PlayerController = nullptr;

}

void UNPD_PlayerComponentBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (!GameInstance)
		GameInstance = Cast<UNPD_GameInstance>(GetWorld()->GetGameInstance());
	if (!Player)
		Player = Cast<ANPD_PlayerCharacter>(GetOwner());
	if (!PlayerController)
		PlayerController = Cast<ANPD_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
}

