// Fill out your copyright notice in the Description page of Project Settings.


#include "TaggingSystemComponent.h"

// Sets default values for this component's properties
UTaggingSystemComponent::UTaggingSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


}


// Called when the game starts
void UTaggingSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UTaggingSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTaggingSystemComponent::TryTag(FHitResult TagHitResult)
{
	
	//	ADecalActor* Decal = GetWorld()->SpawnActor<ADecalActor>(Hit)
	//https://forums.unrealengine.com/t/how-to-spawn-a-decal-in-c/419838
}

