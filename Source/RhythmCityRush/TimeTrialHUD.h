// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "TimeTrialHUD.generated.h"

/**
 * 
 */
UCLASS()
class RHYTHMCITYRUSH_API UTimeTrialHUD : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ammoText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* timerText;

	UPROPERTY(EditAnywhere)
	float StartSeconds;

private:

	UFUNCTION()
	void OnSprayPaintCansChanged(float AmmoValue);
	
};
