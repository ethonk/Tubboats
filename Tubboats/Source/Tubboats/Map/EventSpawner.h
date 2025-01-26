// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Tubboats/Events/EventBase.h"
#include "EventSpawner.generated.h"

UCLASS()
class TUBBOATS_API AEventSpawner : public AActor
{
	GENERATED_BODY()
	
public:

#pragma region Core

	AEventSpawner();

	virtual void BeginPlay() override;
	
#pragma endregion

#pragma region Spawning

	void SpawnRandomEvent();
	
	UFUNCTION(BlueprintCallable)
	void StartSpawningEvents();

	UFUNCTION(BlueprintCallable)
	void StopSpawningEvents();

	UFUNCTION(BlueprintCallable)
	void DestroyAllEvents();
	
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
	TArray<AEventBase*> ActiveEvents;
	
	// Timer Handle
	
	UPROPERTY(Transient)
	FTimerHandle SpawnerTimerHandle;

#pragma endregion
	
#pragma region Properties

	// Spawning

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Properties|Spawning")
	TArray<TSubclassOf<AEventBase>> SpawnableEvents;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Properties|Spawning")
	float SpawnDelay = 20.f;
	
#pragma endregion

};
