// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaseEnemy.h"

#include "ChaseEnemyController.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "AITypes.h"

// Sets default values
AChaseEnemy::AChaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCollisionDetection = CreateDefaultSubobject<USphereComponent>("Player Collision Detection");
	PlayerCollisionDetection->SetupAttachment(RootComponent);

	PlayerAttackCollisionDetection = CreateDefaultSubobject<USphereComponent>("Player Attack Collision Detection");
	PlayerAttackCollisionDetection->SetupAttachment(RootComponent);

	DamageCollision = CreateDefaultSubobject<UBoxComponent>("Damage Collision");
	DamageCollision->SetupAttachment(RootComponent); // ToDo: Connect to socket when animated
	
}

// Called when the game starts or when spawned
void AChaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	ChaseEnemyController = Cast<AChaseEnemyController>(GetController());
	ChaseEnemyController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AChaseEnemy::OnAIMoveCompleted);
	
}

void AChaseEnemy::OnAIMoveCompleted(FAIRequestID, const FPathFollowingResult& Result)
{
	ChaseEnemyController->RandomPatrol();
}

// Called every frame
void AChaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AChaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

