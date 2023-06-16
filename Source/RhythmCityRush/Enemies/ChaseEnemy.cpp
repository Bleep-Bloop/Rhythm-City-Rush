// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaseEnemy.h"

#include "ChaseEnemyController.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "AITypes.h"
#include "RhythmCityRush/Player/RhythmCityRushCharacter.h"

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
	
	ChaseEnemyAIController = Cast<AChaseEnemyController>(GetController());
	ChaseEnemyAIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AChaseEnemy::OnAIMoveCompleted);

	PlayerCollisionDetection->OnComponentBeginOverlap.AddDynamic(this, &AChaseEnemy::OnPlayerDetectedOverlapBegin);
	PlayerCollisionDetection->OnComponentEndOverlap.AddDynamic(this, &AChaseEnemy::OnPlayerDetectedOverlapEnd);

	PlayerAttackCollisionDetection->OnComponentBeginOverlap.AddDynamic(this, &AChaseEnemy::OnPlayerAttackOverlapBegin);
	PlayerAttackCollisionDetection->OnComponentEndOverlap.AddDynamic(this, &AChaseEnemy::OnPlayerAttackOverlapEnd);

	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &AChaseEnemy::OnDealDamageOverlapBegin);
	
}

void AChaseEnemy::OnAIMoveCompleted(FAIRequestID, const FPathFollowingResult& Result)
{
	ChaseEnemyAIController->RandomPatrol();
}

void AChaseEnemy::OnPlayerDetectedOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AChaseEnemy::OnPlayerDetectedOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AChaseEnemy::OnPlayerAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AChaseEnemy::OnPlayerAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AChaseEnemy::OnDealDamageOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AChaseEnemy::MoveToPlayer()
{
	ChaseEnemyAIController->MoveToLocation(PlayerCharacter->GetActorLocation(), StoppingDistance, true, true);
}

void AChaseEnemy::SeekPlayer()
{
	MoveToPlayer();
	GetWorld()->GetTimerManager().SetTimer(SeekPlayerTimerHandle, this, &AChaseEnemy::SeekPlayer, 0.25, true);
}

void AChaseEnemy::StopSeekingPlayer()
{
	GetWorld()->GetTimerManager().ClearTimer(SeekPlayerTimerHandle);
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

