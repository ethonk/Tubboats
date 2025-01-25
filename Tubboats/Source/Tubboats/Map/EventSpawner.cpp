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
	// Validate
	if (SpawnableEvents.IsEmpty()) { return; }

	// Get random event & location
	const TSubclassOf<AEventBase> RandomEvent = SpawnableEvents[FMath::RandRange(0, SpawnableEvents.Num() - 1)];
	const FVector RandomLocation = GetRandomSpawnLocation();

	// Spawn event
	AEventBase* NewEvent = GetWorld()->SpawnActor<AEventBase>(RandomEvent, RandomLocation, FRotator::ZeroRotator);
	if (!NewEvent) { return; }

	// Add to array
	ActiveEvents.Add(NewEvent);
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

void AEventSpawner::DestroyAllEvents()
{
	// Iterate destroy all events
	for (AEventBase* Event : ActiveEvents)
	{
		if (!Event) { continue; }
		Event->Destroy();
	}

	// Clear array
	ActiveEvents.Empty();
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