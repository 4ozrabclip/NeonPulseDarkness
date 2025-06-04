// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/NPD_WidgetBase.h"
#include "NPD_DialogueWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class NEONPULSEDARK_API UNPD_DialogueWidget : public UNPD_WidgetBase
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	void SetText(FColor TextColour = FColor::White, const FString& InText = "");

protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UTextBlock* DialogueText;
	
	
};
