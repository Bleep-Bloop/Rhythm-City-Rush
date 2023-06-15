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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class RHYTHMCITYRUSH_API UTaggingSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UTaggingSystemComponent();
	
protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<UMaterialInstance*> SmallGrfTagMaterialInstances;

	UPROPERTY(EditDefaultsOnly)
	TArray<UMaterialInstance*> MediumGrfTagMaterialInstances;

	UPROPERTY(EditDefaultsOnly)
	TArray<UMaterialInstance*> LargeGrfTagMaterialInstances;

public:	
	
	UPROPERTY(EditAnywhere, Category = Graffiti)
	UMaterialInterface* GrfTagDecalToSpawn;
	
	UPROPERTY(EditAnywhere)
	FVector DecalSize;

	UMaterialInstance* GetRandomGrfTag(EGrfTagSizes GrfTagSize);
	
};
