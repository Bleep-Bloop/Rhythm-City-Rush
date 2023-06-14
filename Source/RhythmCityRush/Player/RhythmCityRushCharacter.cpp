// Fill out your copyright notice in the Description page of Project Settings.


#include "RhythmCityRushCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "RCRCharacterMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RhythmCityRush/InteractableEnvironment/GrindableRail.h"

ARhythmCityRushCharacter::ARhythmCityRushCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<URCRCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RCRCharacterMovementComponent = Cast<URCRCharacterMovementComponent>(GetCharacterMovement());
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->MaxWalkSpeed = 500.f; 
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->GroundFriction = 0;
	GetCharacterMovement()->BrakingDecelerationWalking = 0; 
	GetCharacterMovement()->bUseSeparateBrakingFriction = true; 
	
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f; 
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 650.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
}

// Called when the game starts or when spawned
void ARhythmCityRushCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Create the chosen GrindControllerComponent
	//GrindControllerComponent = NewObject<UGrindControllerComponent>(this, GrindControllerComponentBP, "Players Grind Controller",
	//	RF_NoFlags, nullptr, false, nullptr, nullptr);
	RCRCharacterMovementComponent = GetComponentByClass<URCRCharacterMovementComponent>();

	bCanMove = true;
	
}

void ARhythmCityRushCharacter::Tag()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "TAG");
}

// Called every frame
void ARhythmCityRushCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARhythmCityRushCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Setup Action Bindings
	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARhythmCityRushCharacter::Move);

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ARhythmCityRushCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ARhythmCityRushCharacter::StopJumping);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARhythmCityRushCharacter::Look);

		// Tagging
		EnhancedInputComponent->BindAction(TagAction, ETriggerEvent::Triggered, this, &ARhythmCityRushCharacter::Tag);
	}

}

void ARhythmCityRushCharacter::Move(const FInputActionValue& Value)
{

	if(!bCanMove)
		return;
	
	// Input is a Vector2D
	MovementVector = Value.Get<FVector2D>();
	
	if(Controller != nullptr)
	{
		// Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator  YawRotation(0, Rotation.Yaw, 0);

		// Get Forward Vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// Get Right Vector
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// If the player pulls the thumbstick back increase braking.
		if(MovementVector.Y < -0.95)
		{
			// Increase to bring character to a stop when pulled back
			GetCharacterMovement()->BrakingDecelerationWalking = 1500;
		}
		else
		{
			AddMovementInput(ForwardDirection, MovementVector.Y);
			AddMovementInput(RightDirection, MovementVector.X);
			GetCharacterMovement()->BrakingDecelerationWalking = 0;
		}
	}
}

void ARhythmCityRushCharacter::Look(const FInputActionValue& Value)
{

	// Input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if(Controller != nullptr)
	{
		// Add Yaw and Pitch Input to Controller
		AddControllerPitchInput(LookAxisVector.Y); 
		AddControllerYawInput(LookAxisVector.X);
	}
	
}

void ARhythmCityRushCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if(Hit.GetActor()->GetClass()->IsChildOf(AGrindableRail::StaticClass()))
	{
		if(RCRCharacterMovementComponent)
		{
			RCRCharacterMovementComponent->StartGrind(Hit, Cast<AGrindableRail>(Hit.GetActor())->SplineComponent, GetCapsuleComponent(), GetMesh(), this);
		}
			
	}
	
}

FCollisionQueryParams ARhythmCityRushCharacter::GetIgnoreCharacterParams() const
{
	FCollisionQueryParams Params;

	TArray<AActor*> CharacterChildren;
	GetAllChildActors(CharacterChildren);
	Params.AddIgnoredActors(CharacterChildren);
	Params.AddIgnoredActor(this);

	return Params;
}

bool ARhythmCityRushCharacter::GetCanMove()
{
	return bCanMove;
}

void ARhythmCityRushCharacter::SetCanMove(bool NewState)
{
	bCanMove = NewState;
}

