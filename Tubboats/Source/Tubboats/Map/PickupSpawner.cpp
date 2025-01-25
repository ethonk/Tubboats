// Fill out your copyright notice in the Description page of Project Settings.


#include "../Map/PickupSpawner.h"

#include "Kismet/KismetMathLibrary.h"


#pragma region Core

APickupSpawner::APickupSpawner()
{
	// Create Extent
	SpawnExtents = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Extents"));
	RootComponent = SpawnExtents;
}

void APickupSpawner::BeginPlay()
{
	Super::BeginPlay();
}

#pragma endregion

#pragma region Spawning

void APickupSpawner::SpawnRandomPickup()
{
	// Check valid pickup and we don't exceed max
	if (SpawnablePickups.IsEmpty() || SpawnedPickups.Num() >= MaxSpawnedPickups) { return; }

	// Get random pickup & location
	const TSubclassOf<APickupBase> RandomPickup = SpawnablePickups[FMath::RandRange(0, SpawnablePickups.Num() - 1)];
	const FVector RandomLocation = GetRandomSpawnLocation();

	// Spawn pickup
	APickupBase* NewPickup = GetWorld()->SpawnActor<APickupBase>(RandomPickup, RandomLocation, FRotator::ZeroRotator);
	if (!NewPickup) { return; }

	// Add to array and subscribe to destroyed
	SpawnedPickups.Add(NewPickup);
	NewPickup->OnPickupDestroyed.AddDynamic(this, &APickupSpawner::OnPickupDestroyed);
}

void APickupSpawner::StartSpawning()
{
	// Start Timer
	GetWorld()->GetTimerManager().SetTimer(SpawnerTimerHandle, this, &APickupSpawner::SpawnRandomPickup,
		SpawnDelay, true);
}

void APickupSpawner::StopSpawning()
{
	// Stop Timer
	GetWorld()->GetTimerManager().ClearTimer(SpawnerTimerHandle);
}

void APickupSpawner::OnPickupDestroyed(APickupBase* Pickup)
{
	// Remove from array
	SpawnedPickups.Remove(Pickup);

	// Clean array
	for (int i = SpawnedPickups.Num() - 1; i >= 0; --i)
	{
		if (!SpawnedPickups[i]) { SpawnedPickups.RemoveAt(i); }
	}
}

void APickupSpawner::DestroyAllPickups()
{
	// Reverse iterate, destroy and remove
	for (int i = SpawnedPickups.Num() - 1; i >= 0; --i)
	{
		if (!SpawnedPickups[i]) { return; }
		
		// unsubscribe all from destroyed if bound
		if (SpawnedPickups[i]->OnPickupDestroyed.IsBound()) { SpawnedPickups[i]->OnPickupDestroyed.Clear(); }
		
		// destroy
		SpawnedPickups[i]->Destroy();
	}

	// Safety, clear array
	SpawnedPickups.Empty();
}

#pragma endregion

#pragma region Getters

FVector APickupSpawner::GetRandomSpawnLocation() const
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