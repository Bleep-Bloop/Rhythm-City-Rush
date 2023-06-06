// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../RhythmCityRush.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RCRCharacterMovementComponent.generated.h"

// NOTE - WallRide can only be used on objects tagged 'WallRidable'

UENUM(BlueprintType)
enum ECustomMovementMode
{
	CMOVE_None		UMETA(Hidden),
	CMOVE_WallRide	UMETA(DisplayName = "Wall Ride"),
	CMOVE_Grind		UMETA(DisplayName = "Grinding"),
	CMOVE_MAX		UMETA(Hidden),
};

UCLASS()
class RHYTHMCITYRUSH_API URCRCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	

	// Wall Ride Properties
	UPROPERTY(EditDefaultsOnly) float MinWallRideSpeed = 200.f;			// Minimum speed to begin a wall ride.
	UPROPERTY(EditDefaultsOnly) float MaxWallRideSpeed = 800.f;			// Max speed of a wall ride.
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

public:
	UFUNCTION(BlueprintPure)
	bool IsCustomMovementMode(ECustomMovementMode InCustomMovementMode) const; // ToDo: Rename
	UFUNCTION(BlueprintPure)
	bool IsMovementMode(EMovementMode InMovementMode) const;

	UFUNCTION(BlueprintPure)
	bool IsWallRiding() const { return IsCustomMovementMode(CMOVE_WallRide); }
	UFUNCTION(BlueprintPure)
	bool WallRidingIsRight() const { return bWallRideIsRight; }

private:
	// Returns owner's capsule component's scaled radius/
	float CapR() const;
	// Returns owner's capsule component's half height.
	float CapHH() const;
	
};
