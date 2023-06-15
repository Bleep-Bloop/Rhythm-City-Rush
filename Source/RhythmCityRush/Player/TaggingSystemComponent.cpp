// Fill out your copyright notice in the Description page of Project Settings.


#include "TaggingSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTaggingSystemComponent::UTaggingSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
}

// Called when the game starts
void UTaggingSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// Temp
	//DecalSize = FVector(32.0, 64.0, 64.0f);
	
}

UMaterialInstance* UTaggingSystemComponent::GetRandomGrfTag(EGrfTagSizes GrfTagSize)
{

	int MaxRandom;

	switch (GrfTagSize)
	{
	case EGrfTagSizes::Small:
		MaxRandom = SmallGrfTagMaterialInstances.Num();
		break;
	case EGrfTagSizes::Medium:
		MaxRandom = MediumGrfTagMaterialInstances.Num();
		break;
	case EGrfTagSizes::Large:
		MaxRandom = MediumGrfTagMaterialInstances.Num();
		break;
	default: MaxRandom = 1;
	}
		
	int RandomNumberInRange = FMath::RandRange(0, MaxRandom);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("%d"), RandomNumberInRange));

	return nullptr;
	
}
