// Fill out your copyright notice in the Description page of Project Settings.


#include "RCRCharacterMovementComponent.h"

#include "RhythmCityRushCharacter.h"
#include "Components/CapsuleComponent.h"

URCRCharacterMovementComponent::URCRCharacterMovementComponent()
{
}

void URCRCharacterMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();

	RCRCharacterOwner = Cast<ARhythmCityRushCharacter>(GetOwner());
}

// Getters / Helpers
bool URCRCharacterMovementComponent::IsMovingOnGround() const
{
	return Super::IsMovingOnGround();
}

float URCRCharacterMovementComponent::GetMaxSpeed() const
{
	if (MovementMode != MOVE_Custom)
		return Super::GetMaxSpeed();

	switch (CustomMovementMode)
	{
	case CMOVE_WallRide:
		return MaxWallRideSpeed;
	default:
		UE_LOG(LogTemp, Fatal, TEXT("Invalid Movement Mode"));
		return -1.0f;
	}
}

float URCRCharacterMovementComponent::GetMaxBrakingDeceleration() const
{
	if (MovementMode != MOVE_Custom)
		return Super::GetMaxBrakingDeceleration();

	switch (CustomMovementMode)
	{
	case CMOVE_WallRide:
		return 0.0f;
	default:
		UE_LOG(LogTemp, Fatal, TEXT("Invalid Movement Mode"));
		return -1.0f;
	}
}

// Jumping
bool URCRCharacterMovementComponent::CanAttemptJump() const
{
	return Super::CanAttemptJump() || IsWallRiding();
}

bool URCRCharacterMovementComponent::DoJump(bool bReplayingMoves)
{
	bool bWasWallRiding = IsWallRiding();
	if(Super::DoJump(bReplayingMoves))
	{
		if(bWasWallRiding)
		{
			FVector Start = UpdatedComponent->GetComponentLocation();
			FVector CastDelta = UpdatedComponent->GetRightVector() * CapR() * 2;
			FVector End = bWallRideIsRight ? Start + CastDelta : Start - CastDelta;
			auto Params = RCRCharacterOwner->GetIgnoreCharacterParams();
			FHitResult WallHit;
			GetWorld()->LineTraceSingleByProfile(WallHit, Start, End, "BlockAll", Params);
			Velocity += WallHit.Normal * WallJumpOffForce;
		}
		return true;
	}
	return false;
}

// Movement Pipeline
void URCRCharacterMovementComponent::UpdateCharacterStateBeforeMovement(float DeltaSeconds)
{
	if(IsFalling())
		TryWallRide();

	Super::UpdateCharacterStateBeforeMovement(DeltaSeconds);
}

void URCRCharacterMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{
	Super::PhysCustom(deltaTime, Iterations);

	switch (CustomMovementMode)
	{
	case CMOVE_WallRide:
		PhysWallRide(deltaTime, Iterations);
		break;
	default:
		UE_LOG(LogTemp, Fatal, TEXT("Invalid Movement Mode"));
	}
}

// Movement Event
void URCRCharacterMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);

	if(IsFalling())
		bOrientRotationToMovement = true;

	if(IsWallRiding() && GetOwnerRole() == ROLE_SimulatedProxy)
	{
		FVector Start = UpdatedComponent->GetComponentLocation();
		FVector End = Start + UpdatedComponent->GetRightVector() * CapR() * 2;
		auto Params = RCRCharacterOwner->GetIgnoreCharacterParams();
		FHitResult WallHit;
		bWallRideIsRight = GetWorld()->LineTraceSingleByProfile(WallHit, Start, End, "BlockAll", Params);
	}
}

bool URCRCharacterMovementComponent::TryWallRide()
{
	if(!IsFalling())
		return false;

	if(Velocity.SizeSquared2D() < pow(MinWallRideSpeed, 2))
		return false;

	if(Velocity.Z < -MaxVerticalWallRideSpeed)
		return false;

	FVector Start = UpdatedComponent->GetComponentLocation();
	FVector LeftEnd = Start - UpdatedComponent->GetRightVector() * CapR() * 2;
	FVector RightEnd = Start + UpdatedComponent->GetRightVector() * CapR() * 2;
	auto Params = RCRCharacterOwner->GetIgnoreCharacterParams();
	FHitResult FloorHit, WallHit;

	// Check Player Height;
	if(GetWorld()->LineTraceSingleByProfile(FloorHit, Start, Start + FVector::DownVector * (CapHH() + MinWallRideHeight), "BlockAll", Params))
	{
		return false;
	}

	// Left Cast
	GetWorld()->LineTraceSingleByProfile(WallHit, Start, LeftEnd, "BlockAll", Params);
	if(WallHit.IsValidBlockingHit() && (Velocity | WallHit.Normal) < 0 && WallHit.GetComponent()->ComponentHasTag("WallRidable"))
		bWallRideIsRight = false;
	// Right Cast
	else
	{
		GetWorld()->LineTraceSingleByProfile(WallHit, Start, RightEnd, "BlockAll", Params);
		if(WallHit.IsValidBlockingHit() && (Velocity | WallHit.Normal) < 0 && WallHit.GetComponent()->ComponentHasTag("WallRidable"))
			bWallRideIsRight = true;
		else
			return false;
	}

	FVector ProjectedVelocity = FVector::VectorPlaneProject(Velocity, WallHit.Normal);
	if(ProjectedVelocity.SizeSquared2D() < pow(MinWallRideSpeed, 2))
		return false;

	// Passed All Conditions
	Velocity = ProjectedVelocity;
	Velocity.Z = FMath::Clamp(Velocity.Z, 0.0f, MaxVerticalWallRideSpeed);
	SetMovementMode(MOVE_Custom, CMOVE_WallRide);
	return true;
}

void URCRCharacterMovementComponent::PhysWallRide(float deltaTime, int32 Iterations)
{
	if(deltaTime < MIN_TICK_TIME)
		return;

	if (!CharacterOwner || (!CharacterOwner->Controller && !bRunPhysicsWithNoController && !HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity() && (CharacterOwner->GetLocalRole() != ROLE_SimulatedProxy)))
	{
		Acceleration = FVector::ZeroVector;
		Velocity = FVector::ZeroVector;
		return;
	}

	bJustTeleported = false;
	float RemainingTime = deltaTime;

	// Perform The Move
	while ( (RemainingTime >= MIN_TICK_TIME) && (Iterations < MaxSimulationIterations) && CharacterOwner && (CharacterOwner->Controller || bRunPhysicsWithNoController || (CharacterOwner->GetLocalRole() == ROLE_SimulatedProxy)) )
	{
		Iterations++;
		bJustTeleported = false;
		const float timeTick = GetSimulationTimeStep(RemainingTime, Iterations);
		RemainingTime -= timeTick;
		const FVector OldLocation = UpdatedComponent->GetComponentLocation();

		FVector Start = UpdatedComponent->GetComponentLocation();
		FVector CastDelta = UpdatedComponent->GetRightVector() * CapR() * 2;
		FVector End = bWallRideIsRight ? Start + CastDelta : Start - CastDelta;
		auto Params = RCRCharacterOwner->GetIgnoreCharacterParams();
		float SinPullAwayAngle = FMath::Sin(FMath::DegreesToRadians(WallRidePullAwayAngle));
		FHitResult WallHit;
		GetWorld()->LineTraceSingleByProfile(WallHit, Start, End, "BlockAll", Params);
		bool bWantsToPullAway = WallHit.IsValidBlockingHit() && !Acceleration.IsNearlyZero() && (Acceleration.GetSafeNormal() | WallHit.Normal) > SinPullAwayAngle;
		if(!WallHit.IsValidBlockingHit() || bWantsToPullAway || !WallHit.GetComponent()->ComponentHasTag("WallRidable"))
		{
			SetMovementMode(MOVE_Falling);
			StartNewPhysics(RemainingTime, Iterations);
			return;
		}
		
		// Clamp Acceleration
		Acceleration = FVector::VectorPlaneProject(Acceleration, WallHit.Normal);
		Acceleration.Z = 0.0f;

		// Apply Acceleration
		CalcVelocity(timeTick, 0.0f, false, GetMaxBrakingDeceleration());
		Velocity = FVector::VectorPlaneProject(Velocity, WallHit.Normal);
		float TangentAccel = Acceleration.GetSafeNormal() | Velocity.GetSafeNormal2D();
		bool bVelUp = Velocity.Z > 0.0f;
		Velocity.Z += GetGravityZ() * WallRideGravityScaleCurve->GetFloatValue(bVelUp ? 0.0f : TangentAccel) * timeTick;
		if(Velocity.SizeSquared2D() < pow(MinWallRideSpeed, 2) || Velocity.Z < -MaxVerticalWallRideSpeed)
		{
			SetMovementMode(MOVE_Falling);
			StartNewPhysics(RemainingTime, Iterations);
			return;
		}

		// Compute Move Parameters
		const FVector Delta = timeTick * Velocity; // dx = v * dt
		const bool bZeroDelta = Delta.IsNearlyZero();
		if(bZeroDelta)
			RemainingTime = 0.0f;
		else
		{
			FHitResult Hit;
			SafeMoveUpdatedComponent(Delta, UpdatedComponent->GetComponentQuat(), true, Hit);
			FVector WallAttractionDelta = -WallHit.Normal * WallAttractionForce * timeTick;
			SafeMoveUpdatedComponent(WallAttractionDelta, UpdatedComponent->GetComponentQuat(), true, Hit);
		}
		if(UpdatedComponent->GetComponentLocation() == OldLocation)
		{
			RemainingTime = 0.0f;
			break;
		}
		Velocity = (UpdatedComponent->GetComponentLocation() - OldLocation) / timeTick; // v = dx / dt
	}

	FVector Start = UpdatedComponent->GetComponentLocation();
	FVector CastDelta = UpdatedComponent->GetRightVector() * CapR() * 2;
	FVector End = bWallRideIsRight ? Start + CastDelta : Start - CastDelta;
	auto Params = RCRCharacterOwner->GetIgnoreCharacterParams();
	FHitResult FloorHit, WallHit;
	GetWorld()->LineTraceSingleByProfile(WallHit, Start, End, "BlockAll", Params);
	GetWorld()->LineTraceSingleByProfile(FloorHit, Start, Start + FVector::DownVector * (CapHH() + MinWallRideHeight * 0.5f), "BlockAll", Params);
	if(FloorHit.IsValidBlockingHit() || !WallHit.IsValidBlockingHit() || Velocity.SizeSquared2D() < pow(MinWallRideSpeed, 2))
		SetMovementMode(MOVE_Falling);
}

// Helpers

float URCRCharacterMovementComponent::CapR() const
{
	return RCRCharacterOwner->GetCapsuleComponent()->GetScaledCapsuleRadius();
}

float URCRCharacterMovementComponent::CapHH() const
{
	return RCRCharacterOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
}

// Interface
bool URCRCharacterMovementComponent::IsCustomMovementMode(ECustomMovementMode InCustomMovementMode) const
{
	return MovementMode == MOVE_Custom && CustomMovementMode == InCustomMovementMode;
}

bool URCRCharacterMovementComponent::IsMovementMode(EMovementMode InMovementMode) const
{
	return InMovementMode == MovementMode;
}
