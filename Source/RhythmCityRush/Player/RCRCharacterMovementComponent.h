// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../RhythmCityRush.h"
#include "Components/SplineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RhythmCityRush/InteractableEnvironment/GrindControllerComponent.h"
#include "RCRCharacterMovementComponent.generated.h"

// NOTE - WallRide can only be used on meshes with Component Tag: 'WallRideable'

UENUM(BlueprintType)
enum ECustomMovementMode
{
	CMOVE_None		UMETA(Hidden),
	CMOVE_WallRide	UMETA(DisplayName = "Wall Ride"),
	CMOVE_MAX		UMETA(Hidden),
};

UCLASS()
class RHYTHMCITYRUSH_API URCRCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	

	// Wall Ride Properties
	UPROPERTY(EditDefaultsOnly) float MinWallRideSpeed = 200.f;			// Minimum speed to begin a wall ride.
	UPROPERTY(EditDefaultsOnly) float MaxWallRideSpeed = 800.f;			// Max speed the wall can be riden at. ?/??wowrdin!
	UPROPERTY(EditDefaultsOnly) float MaxVerticalWallRideSpeed = 200.f; 
	UPROPERTY(EditDefaultsOnly) float WallRidePullAwayAngle = 75;		// When the player input pulls away from the wall at this angle they exit.
	UPROPERTY(EditDefaultsOnly) float WallAttractionForce = 200.f;		// Force pulling the player into the wall.
	UPROPERTY(EditDefaultsOnly) float MinWallRideHeight = 50.f;			// Minimum height off the ground the player must be to wall ride. Measured from bottom of capsule.
	UPROPERTY(EditDefaultsOnly) float WallJumpOffForce = 300.f;
	UPROPERTY(EditDefaultsOnly) UCurveFloat* WallRideGravityScaleCurve;
	
	// Transient
	UPROPERTY(Transient)
	ARhythmCityRushCharacter* RCRCharacterOwner;

	// Flags
	bool bWallRideIsRight;

public:
	URCRCharacterMovementComponent();

protected:

	virtual void BeginPlay() override;
	
	virtual void InitializeComponent() override;
	
	virtual bool CanAttemptJump() const override;
	virtual bool DoJump(bool bReplayingMoves) override;
	
	bool TryWallRide();
	void PhysWallRide(float deltaTime, int32 Iterations);
	
	virtual void UpdateCharacterStateBeforeMovement(float DeltaSeconds) override;
	
	virtual void PhysCustom(float deltaTime, int32 Iterations) override;
	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;

	virtual bool IsMovingOnGround() const override;
	
	virtual float GetMaxSpeed() const override;
	virtual float GetMaxBrakingDeceleration() const override;

	// The BP of the GrindControllerComponent to be instantiated
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grinding)
	TSubclassOf<UGrindControllerComponent> GrindControllerComponentBP;

	UPROPERTY(EditAnywhere, Category = Grinding)
	UGrindControllerComponent* GrindControllerComponent;

public:
	UFUNCTION(BlueprintPure)
	bool IsCustomMovementMode(ECustomMovementMode InCustomMovementMode) const; // ToDo: Rename
	UFUNCTION(BlueprintPure)
	bool IsMovementMode(EMovementMode InMovementMode) const;

	UFUNCTION(BlueprintPure)
	bool IsWallRiding() const { return IsCustomMovementMode(CMOVE_WallRide); }
	UFUNCTION(BlueprintPure)
	bool WallRidingIsRight() const { return bWallRideIsRight; }

	// Call the BP Implemented Grind from GrindControllerComponent
	void StartGrind(FHitResult LandingHit, USplineComponent* RailSpline, UCapsuleComponent* CapsuleComponent, USkeletalMeshComponent* SkeletalMesh, ACharacter* PlayerChar) const;

private:
	// Returns owner's capsule component's scaled radius/
	float CapR() const;
	// Returns owner's capsule component's half height.
	float CapHH() const;
	
};
