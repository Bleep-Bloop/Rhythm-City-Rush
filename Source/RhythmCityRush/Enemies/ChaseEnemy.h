// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ChaseEnemy.generated.h"

UCLASS()
class RHYTHMCITYRUSH_API AChaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AChaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class AChaseEnemyController* ChaseEnemyController;
	
	void OnAIMoveCompleted(struct FAIRequestID, const struct FPathFollowingResult& Result);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	bool PlayerDetected;
	bool bCanAttackPlayer;

	UPROPERTY(BlueprintReadWrite)
	bool CanDealDamage;

	class ARhythmCityRushCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere)
	class USphereComponent* PlayerCollisionDetection;

	UPROPERTY(EditAnywhere)
	class USphereComponent* PlayerAttackCollisionDetection;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* DamageCollision;

	

};
