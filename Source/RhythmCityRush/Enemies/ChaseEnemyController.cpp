// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaseEnemyController.h"

#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"

void AChaseEnemyController::BeginPlay()
{
	Super::BeginPlay();

	NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

	RandomPatrol();
	
}

void AChaseEnemyController::RandomPatrol()
{

	if(NavArea)
	{
		NavArea->K2_GetRandomReachablePointInRadius(GetWorld(), GetPawn()->GetActorLocation(), RandomLocation, 15000.0f);

		MoveToLocation(RandomLocation);
	}
	
}
