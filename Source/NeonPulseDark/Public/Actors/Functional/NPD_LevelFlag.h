// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPD_FunctionalActor.h"
#include "NeonPulseDark/Public/Data/Structs/LevelData.h"
#include "NPD_LevelFlag.generated.h"

class UPointLightComponent;
class UBoxComponent;

UCLASS(Abstract)
class NEONPULSEDARK_API ANPD_LevelFlag : public ANPD_FunctionalActor
{
	GENERATED_BODY()
public:
	ANPD_LevelFlag();
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	             int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Flag Type")
	ELevelFlagType FlagType;

public:
protected:
	// Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* TriggerBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UPointLightComponent* Light;

	
};
