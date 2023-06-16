// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup_SprayCan.h"

// Sets default values
APickup_SprayCan::APickup_SprayCan()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Spray Can Static Mesh");
	RootComponent = StaticMeshComponent;

	StaticMeshComponent->SetEnableGravity(false);
	StaticMeshComponent->SetGenerateOverlapEvents(true);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	OnActorBeginOverlap.AddDynamic(this, &APickup_SprayCan::OnOverlapBegin);
	
}

// Called when the game starts or when spawned
void APickup_SprayCan::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup_SprayCan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup_SprayCan::PickUp(ARhythmCityRushCharacter* GrabbingCharacter)
{
	if(GrabbingCharacter->PickupSprayCan())
		DestroyPickup();
}

void APickup_SprayCan::DestroyPickup()
{
	Destroy();
}

void APickup_SprayCan::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if(OtherActor->IsA(ARhythmCityRushCharacter::StaticClass()))
		PickUp(Cast<ARhythmCityRushCharacter>(OtherActor));
}

