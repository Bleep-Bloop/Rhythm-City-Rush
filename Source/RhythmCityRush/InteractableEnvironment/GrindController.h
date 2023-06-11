// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "GameFramework/Actor.h"
#include "GrindController.generated.h"

UCLASS()
class RHYTHMCITYRUSH_API AGrindController : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AGrindController();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Building Spline Rail
	UPROPERTY(VisibleAnywhere, Category = "GrindController")
	USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GrindController")
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GrindController")
	TEnumAsByte<ESplineMeshAxis::Type> ForwardAxis;

	
};
