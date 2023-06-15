// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "TaggingSystemComponent.h"
#include "Camera/CameraComponent.h"
#include "../RhythmCityRush.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "RhythmCityRushCharacter.generated.h"

UCLASS()
class RHYTHMCITYRUSH_API ARhythmCityRushCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
	URCRCharacterMovementComponent* RCRCharacterMovementComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* FollowCamera;

	// The BP of the TaggingSystemComponent to be instantiated
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tagging)
	TSubclassOf<UTaggingSystemComponent> TaggingSystemComponentBP;

	UPROPERTY(EditAnywhere, Category = Tagging)
	UTaggingSystemComponent* TaggingSystemComponent;

public:

	ARhythmCityRushCharacter(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void BeginPlay() override;
	
// Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* TagAction;
	
	// Called for Movement Input
	void Move(const FInputActionValue& Value);

	// Called for Look Input
	void Look(const FInputActionValue& Value);

	virtual void Landed(const FHitResult& Hit) override;
	
	UPROPERTY()
	bool bCanMove;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FCollisionQueryParams GetIgnoreCharacterParams() const;
	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	UFUNCTION(BlueprintPure) FORCEINLINE URCRCharacterMovementComponent* GetRCRCharacterMovementComponent() const { return RCRCharacterMovementComponent; }

	// Double check grind bp unsure if used this
	FVector2D MovementVector; // Testing something

	UFUNCTION(BlueprintCallable)
	bool GetCanMove();

	UFUNCTION(BlueprintCallable)
	void SetCanMove(bool NewState);
	
	void TagWall();
	
};
