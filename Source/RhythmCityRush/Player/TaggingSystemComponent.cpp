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


void UTaggingSystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

UMaterialInstance* UTaggingSystemComponent::GetRandomGrfTag(const EGrfTagSizes GrfTagSize)
{

	int MaxRandom;

	// Return random tag of given size.
	switch (GrfTagSize)
	{
	case EGrfTagSizes::Small:
		MaxRandom = SmallGrfTagMaterialInstances.Num() - 1;
		return SmallGrfTagMaterialInstances[FMath::RandRange(0, MaxRandom)];
	case EGrfTagSizes::Medium:
		MaxRandom = MediumGrfTagMaterialInstances.Num() - 1;
		return MediumGrfTagMaterialInstances[FMath::RandRange(0, MaxRandom)];
	case EGrfTagSizes::Large:
		MaxRandom = MediumGrfTagMaterialInstances.Num() - 1;
		return LargeGrfTagMaterialInstances[FMath::RandRange(0, MaxRandom)];
	default: return SmallGrfTagMaterialInstances[0];
	}
	
}
