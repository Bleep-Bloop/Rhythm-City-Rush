// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "GameFramework/Actor.h"
#include "GrindableRail.generated.h"

UCLASS()
class RHYTHMCITYRUSH_API AGrindableRail : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AGrindableRail();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Building Spline Rail
	UPROPERTY(VisibleAnywhere, Category = "Grindable Rail")
	USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grindable Rail")
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grindable Rail")
	TEnumAsByte<ESplineMeshAxis::Type> ForwardAxis;

	
};
