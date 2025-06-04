// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Functional/NPD_LevelFlag.h"

#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "NeonPulseDark/Public/Game/NPD_GameInstance.h"

ANPD_LevelFlag::ANPD_LevelFlag()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light Component"));
	Light->SetupAttachment(GetRootComponent());
	Light->SetAttenuationRadius(50.f);
	Light->SetIntensity(1.f);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void ANPD_LevelFlag::BeginPlay()
{
	Super::BeginPlay();

	if (TriggerBox)
	{
		TriggerBox->OnComponentBeginOverlap.Clear();
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ANPD_LevelFlag::OnEnter);
	}
	
}

void ANPD_LevelFlag::OnEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
									UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!GameInstance)
		return;
	
	GameInstance->AddLevelFlagToPlayerData(FlagType);

	TriggerBox->SetActive(false);
	RemoveSisterFlag();
}

void ANPD_LevelFlag::RemoveSisterFlag()
{
	if (SisterFlag)
	{
		SisterFlag.Get()->Destroy();
	}
}
