// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TaggingSystemComponent.generated.h"

// ToDo: Make Friend Class - RCRPlayerCharacter?

UENUM()
enum EGrfTagSizes
{
	Small,
	Medium,
	Large,
};

/**
 * @brief  Holds references to a player's GrfTagMaterialInstances.
 * Can return a material instance of a given size for use with TaggableActors.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class RHYTHMCITYRUSH_API UTaggingSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UTaggingSystemComponent();
	
protected:
	/**
	 * @brief 
	 */
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<UMaterialInstance*> SmallGrfTagMaterialInstances;

	UPROPERTY(EditDefaultsOnly)
	TArray<UMaterialInstance*> MediumGrfTagMaterialInstances;

	UPROPERTY(EditDefaultsOnly)
	TArray<UMaterialInstance*> LargeGrfTagMaterialInstances;

public:	
	
	UMaterialInstance* GetRandomGrfTag(const EGrfTagSizes GrfTagSize);
	
};
