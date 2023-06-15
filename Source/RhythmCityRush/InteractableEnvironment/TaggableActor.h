// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "RhythmCityRush/Player/TaggingSystemComponent.h"
#include "TaggableActor.generated.h"

UCLASS()
class RHYTHMCITYRUSH_API ATaggableActor : public AActor
{
	GENERATED_BODY()
	
public:	

	ATaggableActor();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Components)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = Components)
	UBoxComponent* TagZoneTrigger;

	UPROPERTY(EditAnywhere, Category = Components)
	UDecalComponent* TagDecalComponent;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EGrfTagSizes> TagSize;

	UPROPERTY(EditAnywhere)
	bool bIsTagged;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	/**
	 * @brief Make the TagDecalComponent Active and change the Decal Material of the TagDecalComponent on surface.
	 * @param Tag Image to replace default Decal Material.
	 */
	void TagWall(UMaterialInterface* Tag);
	
	EGrfTagSizes GetTagZoneSize() const;

	bool GetIsTagged() const;

};
