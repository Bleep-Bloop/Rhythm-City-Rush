// Fill out your copyright notice in the Description page of Project Settings.


#include "TaggableActor.h"

#include "Components/DecalComponent.h"
#include "RhythmCityRush/Player/RhythmCityRushCharacter.h"

// Sets default values
ATaggableActor::ATaggableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	
	TagZoneTrigger = CreateDefaultSubobject<UBoxComponent>("Trigger Zone");
	TagZoneTrigger->AttachToComponent(StaticMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	TagDecalComponent = CreateDefaultSubobject<UDecalComponent>("Tag Decal");
	TagDecalComponent->AttachToComponent(StaticMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
}

// Called when the game starts or when spawned
void ATaggableActor::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ATaggableActor::OnOverlapBegin);
	
	TagDecalComponent->SetHiddenInGame(true);
	
}


// Called every frame
void ATaggableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATaggableActor::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{

	if(OtherActor->IsA(ARhythmCityRushCharacter::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Set Player Tag");

		Cast<ARhythmCityRushCharacter>(OtherActor)->TagWall();
		
		//TagWall(nullptr);
	}
	
}

void ATaggableActor::TagWall(UMaterialInterface* Tag)
{
	TagDecalComponent->SetDecalMaterial(Tag);
	// ToDo: Depending on future materials, will have to handle size. Ideally all same size though.
	TagDecalComponent->SetHiddenInGame(false);
	

}

