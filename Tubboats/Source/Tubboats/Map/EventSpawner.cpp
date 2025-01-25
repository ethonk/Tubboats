// Fill out your copyright notice in the Description page of Project Settings.


#include "../Map/EventSpawner.h"
#include "Kismet/KismetMathLibrary.h"


#pragma region Core

AEventSpawner::AEventSpawner()
{
	// Create Extent
	SpawnExtents = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Extents"));
	RootComponent = SpawnExtents;
}

void AEventSpawner::BeginPlay()
{
	Super::BeginPlay();
}

#pragma endregion

#pragma region Spawning

void AEventSpawner::SpawnRandomEvent()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SpawnRandomEvent"));
}

void AEventSpawner::StartSpawningEvents()
{
	// Start Timer
	GetWorld()->GetTimerManager().SetTimer(SpawnerTimerHandle, this, &AEventSpawner::SpawnRandomEvent,
		SpawnDelay, true);
}

void AEventSpawner::StopSpawningEvents()
{
	// Stop Timer
	GetWorld()->GetTimerManager().ClearTimer(SpawnerTimerHandle);
}

// TODO implement
void AEventSpawner::DestroyAllEvents()
{
}

#pragma endregion

#pragma region Getters

FVector AEventSpawner::GetRandomSpawnLocation() const
{
	if (!SpawnExtents) { return FVector::ZeroVector; }

	// Get local bounds
	const FVector BoxExtent = SpawnExtents->GetScaledBoxExtent();

	// Get random location
	const FVector RandomPointLocal = UKismetMathLibrary::RandomPointInBoundingBox(FVector::ZeroVector, BoxExtent);
	const FVector RandomPointWorld = SpawnExtents->GetComponentTransform().TransformPosition(RandomPointLocal);

	// Return
	return RandomPointWorld;
}

#pragma endregion