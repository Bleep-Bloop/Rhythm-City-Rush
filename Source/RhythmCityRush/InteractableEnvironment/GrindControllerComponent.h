// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"	
#include "Components/CapsuleComponent.h"
#include "Components/SplineComponent.h"
#include "RhythmCityRush/Player/RhythmCityRushCharacter.h"
#include "GrindControllerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class RHYTHMCITYRUSH_API UGrindControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrindControllerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintImplementableEvent)
	void Grind(FHitResult LandingHit, USplineComponent* RailSpline, ARhythmCityRushCharacter* PlayerChar);
		
};
