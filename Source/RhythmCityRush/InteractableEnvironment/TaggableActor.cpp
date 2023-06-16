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
	OnActorEndOverlap.AddDynamic(this, &ATaggableActor::OnOverlapEnd);

	// TaggableActors start untagged.
	bIsTagged = false;

	// Hide tags until activated
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
		Cast<ARhythmCityRushCharacter>(OtherActor)->EnterTagZone(this);
	}
}

void ATaggableActor::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if(OtherActor->IsA(ARhythmCityRushCharacter::StaticClass()))
	{
		Cast<ARhythmCityRushCharacter>(OtherActor)->ExitTagZone();
	}
}

bool ATaggableActor::TagWall(UMaterialInterface* Tag)
{
	if(Tag)
	{
		TagDecalComponent->SetDecalMaterial(Tag);
		// ToDo: Depending on future materials, will have to handle size.
		TagDecalComponent->SetHiddenInGame(false);
		bIsTagged = true;
		return true;
	}
	else
	{
		return false;
	}
}

EGrfTagSizes ATaggableActor::GetTagZoneSize() const
{
	return TagSize;
}

bool ATaggableActor::GetIsTagged() const
{
	return bIsTagged;
}
