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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	bool bPlayerDetected;
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

// AI Controller

	// Stopping distance between enemy and player.
	UPROPERTY(EditAnywhere)
	float StoppingDistance = 100.0f;

	FTimerHandle SeekPlayerTimerHandle;
	
	class AChaseEnemyController* ChaseEnemyAIController;
	
	void OnAIMoveCompleted(struct FAIRequestID, const struct FPathFollowingResult& Result);
	
	UFUNCTION()
	void OnPlayerDetectedOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlayerDetectedOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnPlayerAttackOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlayerAttackOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnDealDamageOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void MoveToPlayer();

	UFUNCTION()
	void SeekPlayer();

	UFUNCTION()
	void StopSeekingPlayer();

	

	

};
