// Fill out your copyright notice in the Description page of Project Settings.


#include "GrindControllerComponent.h"

// Sets default values for this component's properties
UGrindControllerComponent::UGrindControllerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrindControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Emerald, "GRINDCONTROLLER:BEGIN");
}


