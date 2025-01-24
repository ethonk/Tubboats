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

	void EnterCurrentGameState();
	
	void ExitCurrentGameState();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Game State")
	void BP_OnGameStateChanged(const ETubboatGameState& InState);

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

	// Timers

	UPROPERTY(Transient)
	FTimerHandle ActiveGameTimerHandle;
	
#pragma endregion

#pragma region Properties

	// Timing

	UPROPERTY(EditDefaultsOnly, Category = "Properties|Timing")
	float PreGameDuration = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Properties|Timing")
	float GameDuration = 120.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Properties|Timing")
	float GameEndDuration = 10.0f;

#pragma endregion
	
};
