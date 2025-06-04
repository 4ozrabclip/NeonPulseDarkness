// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Functional/NPD_CompleteMazeDoor.h"

#include "Components/NPD_MazeRunTrackerComponent.h"
#include "Actors/Player/NPD_PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Controllers/NPD_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "NeonPulseDark/Public/Game/NPD_GameInstance.h"

ANPD_CompleteMazeDoor::ANPD_CompleteMazeDoor()
{
	PrimaryActorTick.bCanEverTick = false;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void ANPD_CompleteMazeDoor::BeginPlay()
{
	Super::BeginPlay();

	if (!GameInstance)
		GameInstance = Cast<UNPD_GameInstance>(GetWorld()->GetGameInstance());
	if (!Player)
		Player = Cast<ANPD_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (TriggerBox)
	{
		TriggerBox->OnComponentBeginOverlap.Clear();
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ANPD_CompleteMazeDoor::OnEnter);
	}
}

void ANPD_CompleteMazeDoor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void ANPD_CompleteMazeDoor::OnEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!GameInstance)
		return;
	
	UNPD_MazeRunTrackerComponent* MazeRunData = Cast<UNPD_MazeRunTrackerComponent>(Player->GetComponentByClass<UNPD_MazeRunTrackerComponent>());
	if (!MazeRunData) return;

	const float CompletedTime = MazeRunData->GetCurrentTime();
	
	FString CurrentLevel = GetWorld()->GetCurrentLevel()->GetOutermost()->GetName();

	CurrentLevel = CleanLevelPath(CurrentLevel);
	
	
	GameInstance->SetLevelAsComplete(CurrentLevel, CompletedTime);
	UE_LOG(LogTemp, Display, TEXT("Level V1: %s"), *CurrentLevel);
	
	
	PlayerController = Cast<ANPD_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PlayerController) return;
	
	PlayerController->OpenWidget(EUserInterfaceTypes::MazeTimer, true);
	PlayerController->OpenWidget(EUserInterfaceTypes::MazeComplete);

	constexpr float TimeTilLevelChange = 7.f;

	FTimerHandle TimerTilLevelChange;
	GetWorld()->GetTimerManager().SetTimer(TimerTilLevelChange, this, &ANPD_CompleteMazeDoor::OpenNextLevel, TimeTilLevelChange, false);
	
	
}

void ANPD_CompleteMazeDoor::OpenNextLevel()
{
	FString LevelToOpen = GameInstance->GetRandLevelOnConditional();

	GameInstance->SetCurrentLevel(LevelToOpen);

	if (PlayerController)
		PlayerController->OpenWidget(EUserInterfaceTypes::MazeComplete, true);

	UGameplayStatics::OpenLevel(GetWorld(), FName(LevelToOpen));
}

FString ANPD_CompleteMazeDoor::CleanLevelPath(const FString& Path)
{
	FRegexPattern Pattern(TEXT("/Game/Levels/UEDPIE_\\d+_"));
	FRegexMatcher Matcher(Pattern, Path);
    
	FString CleanedPath = Path;
	if (Matcher.FindNext())
	{
		CleanedPath = Path.Replace(*Matcher.GetCaptureGroup(0), TEXT("/Game/Levels/"));
	}

	return CleanedPath;
}