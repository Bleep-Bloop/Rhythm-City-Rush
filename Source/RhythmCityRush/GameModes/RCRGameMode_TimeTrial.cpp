// Fill out your copyright notice in the Description page of Project Settings.


#include "RCRGameMode_TimeTrial.h"

#include "Kismet/GameplayStatics.h"
#include "RhythmCityRush/InteractableEnvironment/TaggableActor.h"

void ARCRGameMode_TimeTrial::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TaggableActorBPToFind, TaggableActorsInLevel);

	NumberOfTaggableActorsInLevel = TaggableActorsInLevel.Num();
	
}

void ARCRGameMode_TimeTrial::CheckTimeTrialProgress()
{
	const int TaggedActors = CheckTaggedActorsInLevel();
	
	if(TaggedActors >= NumberOfTaggableActorsInLevel)
	{
		EndTimeTrial();
	}
}

void ARCRGameMode_TimeTrial::EndTimeTrial()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Level Complete");
}

int ARCRGameMode_TimeTrial::CheckTaggedActorsInLevel()
{
	int NumberOfTaggedActors = 0;

	for (AActor* TaggedActors : TaggableActorsInLevel)
	{
		if(Cast<ATaggableActor>(TaggedActors)->GetIsTagged())
		{
			NumberOfTaggedActors++;
		}
	}

	return NumberOfTaggedActors;
	
}
