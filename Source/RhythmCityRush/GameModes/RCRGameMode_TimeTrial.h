// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../RhythmCityRushGameModeBase.h"
#include "RhythmCityRush/InteractableEnvironment/TaggableActor.h"
#include "RCRGameMode_TimeTrial.generated.h"

/**
 * A Game Mode where the player must 'tag' all ATaggableActors in the level while
 * a timer records how long it takes. Game Mode ends once the final spot is tagged.
 */
UCLASS()
class RHYTHMCITYRUSH_API ARCRGameMode_TimeTrial : public ARhythmCityRushGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	/**
	* @brief BP of the taggable actors in the level.
	 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> TaggableActorBPToFind;

	/**
	 * @brief All found instances of TaggableActorBPToFind.
	 */
	UPROPERTY(EditAnywhere)
	TArray<AActor*> TaggableActorsInLevel;
	
	UPROPERTY(VisibleAnywhere)
	int NumberOfTaggableActorsInLevel;
	
	void EndTimeTrial();

	/**
	 * @brief Checks through TaggableActorsInLevel[] to see if all are set bIsTagged true.
	 * @return Number of ATaggableActors with bIsTagged true.
	 */
	int CheckTaggedActorsInLevel();

	void StartTimer();

public:
	
	/**
	 * @brief Checks if all TaggableActors in level are tagged and ends game if true.
	 */
	void CheckTimeTrialProgress();

	UPROPERTY(EditAnywhere)
	float StartSeconds;
	
};
