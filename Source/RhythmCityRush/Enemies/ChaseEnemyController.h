// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ChaseEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class RHYTHMCITYRUSH_API AChaseEnemyController : public AAIController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	
private:

	UPROPERTY(VisibleAnywhere)
	class UNavigationSystemV1* NavArea;

	FVector RandomLocation;

public:

	UFUNCTION()
	void RandomPatrol();
	
};
