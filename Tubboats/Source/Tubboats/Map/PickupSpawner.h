// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Tubboats/Pickups/PickupBase.h"
#include "PickupSpawner.generated.h"

UCLASS()
class TUBBOATS_API APickupSpawner : public AActor
{
	GENERATED_BODY()
	
public:

#pragma region Core

	APickupSpawner();

	virtual void BeginPlay() override;
	
#pragma endregion

#pragma region Spawning

	void SpawnRandomPickup();
	
	UFUNCTION(BlueprintCallable)
	void StartSpawning();

	UFUNCTION(BlueprintCallable)
	void StopSpawning();

	UFUNCTION()
	void OnPickupDestroyed(APickupBase* Pickup);

	UFUNCTION(BlueprintCallable)
	void DestroyAllPickups();

#pragma endregion

#pragma region Getters

	UFUNCTION(BlueprintCallable)
	FVector GetRandomSpawnLocation() const;

#pragma endregion
	
	//
	//
	//

#pragma region Components

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* SpawnExtents = nullptr;
	
#pragma endregion

#pragma region States

	// Spawning

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "States|Spawning")
	TArray<APickupBase*> SpawnedPickups;
	
	// Timer Handle
	
	UPROPERTY(Transient)
	FTimerHandle SpawnerTimerHandle;

#pragma endregion
	
#pragma region Properties

	// Spawning

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Properties|Spawning")
	TArray<TSubclassOf<APickupBase>> SpawnablePickups;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Properties|Spawning")
	float SpawnDelay = 5.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Properties|Spawning")
	int32 MaxSpawnedPickups = 10;
	
#pragma endregion
	
};
