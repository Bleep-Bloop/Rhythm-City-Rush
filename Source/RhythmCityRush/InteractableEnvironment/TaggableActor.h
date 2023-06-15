// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "TaggableActor.generated.h"

UCLASS()
class RHYTHMCITYRUSH_API ATaggableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATaggableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = Components)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = Components)
	UBoxComponent* TagZoneTrigger;

	UPROPERTY(EditAnywhere, Category = Components)
	UDecalComponent* TagDecalComponent;

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	/**
	 * @brief Make the TagDecalComponent Active and change the Decal Material of the TagDecalComponent on surface.
	 * @param Tag Image to replace default Decal Material.
	 */
	void TagWall(UMaterialInterface* Tag);

};
