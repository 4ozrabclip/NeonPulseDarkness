// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Functional/NPD_RetrieveNavTool.h"

#include "Actors/Player/NPD_PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Controllers/NPD_PlayerController.h"
#include "Kismet/GameplayStatics.h"

ANPD_RetrieveNavTool::ANPD_RetrieveNavTool()
{
	PrimaryActorTick.bCanEverTick = false;
	NavToolType = ENavigationTool::None;
	
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void ANPD_RetrieveNavTool::BeginPlay()
{
	Super::BeginPlay();

	if (TriggerBox)
	{
		TriggerBox->OnComponentBeginOverlap.Clear();
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ANPD_RetrieveNavTool::OnEnter);

		TriggerBox->OnComponentEndOverlap.Clear();
		TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ANPD_RetrieveNavTool::OnExit);
	}
}

void ANPD_RetrieveNavTool::OnExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!Player)
		Player = Cast<ANPD_PlayerCharacter>(OtherActor);

	if (Player)
		Player->SetCurrentNavTool(NavToolType);

	if (!PlayerController)
		PlayerController = Cast<ANPD_PlayerController>(Player->GetController());

	PlayerController->OpenWidget(EUserInterfaceTypes::NavHelp, true);
}

void ANPD_RetrieveNavTool::OnEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
									UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Player)
		Player = Cast<ANPD_PlayerCharacter>(OtherActor);

	if (Player)
	{
		UE_LOG(LogTemp, Error, TEXT("SET CURRENT NAV TOOL"));
		Player->SetCurrentNavTool(NavToolType);
	}
		

	if (!PlayerController)
		PlayerController = Cast<ANPD_PlayerController>(Player->GetController());

	PlayerController->OpenWidget(EUserInterfaceTypes::NavHelp);
}