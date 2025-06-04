// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/NPD_WidgetBase.h"

#include "Actors/Player/NPD_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "NeonPulseDark/Public/Game/NPD_GameInstance.h"

void UNPD_WidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (!Player)
		Player = Cast<ANPD_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!GameInstance)
		GameInstance = Cast<UNPD_GameInstance>(GetWorld()->GetGameInstance());
}
