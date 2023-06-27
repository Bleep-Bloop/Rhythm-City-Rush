// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeTrialHUD.h"

#include <string>

#include "Kismet/GameplayStatics.h"
#include "Player/RhythmCityRushCharacter.h"

void UTimeTrialHUD::NativeConstruct()
{
	Super::NativeConstruct();

	
	if (ARhythmCityRushCharacter* RhythmCityRushCharacter = Cast<ARhythmCityRushCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		RhythmCityRushCharacter->OnSprayCansChangedDelegate.BindUObject(this, &UTimeTrialHUD::OnSprayPaintCansChanged);
	}

	ammoText->SetText(FText::FromString("CANS"));

	StartSeconds = FPlatformTime::Seconds();
	
}

void UTimeTrialHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (ARhythmCityRushCharacter* RhythmCityRushCharacter = Cast<ARhythmCityRushCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		//RhythmCityRushCharacter->OnSprayCansChangedDelegate.BindUObject(this, &UTimeTrialHUD::OnSprayPaintCansChanged);
		OnSprayPaintCansChanged(RhythmCityRushCharacter->CurrentSprayCans);
	}
	if(timerText)
	{
		float SecondsElapsed = FPlatformTime::Seconds() - StartSeconds;
		timerText->SetText(FText::FromString(FString::SanitizeFloat(SecondsElapsed)));
	}
	
	
}


void UTimeTrialHUD::OnSprayPaintCansChanged(float AmmoValue)
{
	ammoText->SetText(FText::FromString(FString::FromInt(AmmoValue)));

}
