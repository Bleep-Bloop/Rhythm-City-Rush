// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "RhythmCityRushGameModeBase.h"
#include "RhythmCityRushGameModeBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Configure Character Movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ... at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint instead
	// of recompiling to adjust them.
	GetCharacterMovement()->JumpZVelocity = 700.0f;
	GetCharacterMovement()->AirControl = 0.35f; // ToDo: Adjust this, we don't want complete control in air.
	GetCharacterMovement()->MaxWalkSpeed = 500.0f; // ToDo: Adjust this and acceleration and braking.
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f; // Constant opposing force that directly lowers the velocity by a constant value. ToDo: I think 0 would work best, Check if holding back will make character stop. ToDo: This doesnt seem to do anything

	// Rollerblade Feel Properties - These values feel good.
	GetCharacterMovement()->GroundFriction = 0;
	GetCharacterMovement()->BrakingDecelerationWalking = 0; // ToDo: Check hover note in the inspector under CharacterMovement. Interesting stuff in there
	GetCharacterMovement()->bUseSeparateBrakingFriction = true; // BrakingFriction will be used to stop character ToDo: Look into more
	
	
	// Create a Camera Boom (pulls in towards player if there is a collision).
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // Distance the camera follows behind the player.
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller (Question: How will this deal with movement when camera is rotated?).

	// Create the Follow Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of boom and let the boom adjust to match the controller orientation.
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm.

	// Note: The skeletal Mesh and Anim Blueprint references on the Mesh Component (inherited from Character)
	// are set in the derived Blueprint asset named BP_PlayerCharacter (to avoid direct content references in C++).
	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

