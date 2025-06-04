// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Functional/NPD_FunctionalActor.h"

#include "Actors/Player/NPD_PlayerCharacter.h"
#include "Controllers/NPD_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "NeonPulseDark/Public/Game/NPD_GameInstance.h"

ANPD_FunctionalActor::ANPD_FunctionalActor()
{
	PrimaryActorTick.bCanEverTick = true;
	GameInstance = nullptr;
	PlayerController = nullptr;
	Player = nullptr;
}

void ANPD_FunctionalActor::BeginPlay()
{
	Super::BeginPlay();

	if (!GameInstance)
		GameInstance = Cast<UNPD_GameInstance>(GetWorld()->GetGameInstance());
	if (!PlayerController)
    	PlayerController = Cast<ANPD_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!Player)
		Player = Cast<ANPD_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}
