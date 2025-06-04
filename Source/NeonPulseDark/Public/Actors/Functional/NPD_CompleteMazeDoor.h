// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPD_FunctionalActor.h"
#include "GameFramework/Actor.h"
#include "NPD_CompleteMazeDoor.generated.h"


class UNPD_MazeCompleteWidget;
class UBoxComponent;


UCLASS()
class NEONPULSEDARK_API ANPD_CompleteMazeDoor : public ANPD_FunctionalActor
{
	GENERATED_BODY()
public:	
	ANPD_CompleteMazeDoor();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//UFunctions
	UFUNCTION()
	void OnEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OpenNextLevel();

	
	static FString CleanLevelPath(const FString& Path);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	UBoxComponent* TriggerBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Widget")
	UNPD_MazeCompleteWidget* MazeCompleteWidget;
	
private:
	FTimerHandle LevelChangeTimer;
	
};
