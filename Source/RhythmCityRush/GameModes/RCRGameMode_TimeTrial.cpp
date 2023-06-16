// Fill out your copyright notice in the Description page of Project Settings.


#include "RCRGameMode_TimeTrial.h"

#include "Kismet/GameplayStatics.h"
#include "RhythmCityRush/InteractableEnvironment/TaggableActor.h"

void ARCRGameMode_TimeTrial::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TaggableActorBPToFind, TaggableActorsInLevel);

	NumberOfTaggableActorsInLevel = TaggableActorsInLevel.Num();

	StartTimer();
	
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

	float SecondsElapsed = FPlatformTime::Seconds() - StartSeconds;
	
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Level Complete - Time: %f"), SecondsElapsed));
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

void ARCRGameMode_TimeTrial::StartTimer()
{
	StartSeconds = FPlatformTime::Seconds();
}
