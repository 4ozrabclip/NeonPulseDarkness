// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPD_FunctionalActor.h"
#include "GameFramework/Actor.h"
#include "NPD_RetrieveNavTool.generated.h"

class UBoxComponent;
enum class ENavigationTool;

UCLASS()
class NEONPULSEDARK_API ANPD_RetrieveNavTool : public ANPD_FunctionalActor
{
	GENERATED_BODY()

public:
	ANPD_RetrieveNavTool();
protected:
	virtual void BeginPlay() override;


public:
	UFUNCTION()
	void OnEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	             int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NavToolType")
	ENavigationTool NavToolType;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	UBoxComponent* TriggerBox;

	

};
