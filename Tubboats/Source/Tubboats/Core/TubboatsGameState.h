// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/GameStateBase.h"
#include "../TubboatsGameplayTags.h"

#include "TubboatsGameState.generated.h"


#pragma region Enumerations

UENUM(BlueprintType)
enum class ETubboatGameState : uint8
{
	Menu,
	PreGame,
	Gameplay,
	GameEnd
};

#pragma endregion

#pragma region Structures

USTRUCT(BlueprintType)
struct FGameStateMessage
{
	GENERATED_BODY()

	FGameStateMessage() :
		GameState(ETubboatGameState::Menu)
	{}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameStateMessage")
	ETubboatGameState GameState;
};

#pragma endregion


UCLASS()
class TUBBOATS_API ATubboatsGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

#pragma region Core

	ATubboatsGameState();

	virtual void BeginPlay() override;

#pragma endregion

#pragma region Game State Functions

	// Game State
	
	void EnterCurrentGameState();
	
	void ExitCurrentGameState();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Game State")
	void BP_OnGameStateChanged(const ETubboatGameState& InState);

	// Players

	void SpawnAllPlayers();

	void DestroyAllPlayers();

	UFUNCTION(BlueprintCallable)
	void PlayerDied(APawn* DyingPlayer);

	void KillAllPlayersIfNoWinner();

#pragma endregion

#pragma region Helpers

	void PopulateSpawnLocations();

#pragma endregion
	
#pragma region Setters

	UFUNCTION(BlueprintCallable)
	void SetCurrentGameState(const ETubboatGameState& InState);

#pragma endregion

#pragma region Getters

	UFUNCTION(BlueprintCallable)
	float GetCurrentRemainingTime() const;
	
#pragma endregion
	
	//
	//
	//
	
#pragma region States

	// General
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "States")
	ETubboatGameState CurrentGameState = ETubboatGameState::Menu;

	// Player

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "States|Player")
	TArray<APawn*> ActivePlayers;
	
	// Game Objects

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "States|InGame")
	TMap<FVector, FRotator> FoundSpawnLocations;
	
	// Timers

	UPROPERTY(Transient)
	FTimerHandle ActiveGameTimerHandle;
	
#pragma endregion

#pragma region Properties

	// Spawning

	UPROPERTY(EditDefaultsOnly, Category = "Properties|Spawning")
	TSubclassOf<APawn> PlayerClassToSpawn = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Properties|Spawning")
	FName SpawnLocationsTag = "PlayerSpawn";	

	// Players

	UPROPERTY(EditDefaultsOnly, Category = "Properties|Players")
	TArray<UMaterialInterface*> PlayerIndexMaterials;
	
	// Timing

	UPROPERTY(EditDefaultsOnly, Category = "Properties|Timing")
	float PreGameDuration = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Properties|Timing")
	float GameDuration = 120.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Properties|Timing")
	float GameEndDuration = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem* DeathEffect = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* SoundToPlay;

#pragma endregion
	
};