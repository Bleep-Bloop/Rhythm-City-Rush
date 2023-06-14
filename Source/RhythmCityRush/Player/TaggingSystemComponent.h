// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TaggingSystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class RHYTHMCITYRUSH_API UTaggingSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTaggingSystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = Graffiti)
	UMaterialInterface* TagDecalToSpawn;

	void TryTag(FHitResult TagHitResult);

	// Distance the raycast will travel to look for a surface. 
	UPROPERTY(EditAnywhere, Category = Graffiti)
	float TagDistance;

	// ToDo: Friend Class - Player
	
};
