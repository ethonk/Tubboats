// Fill out your copyright notice in the Description page of Project Settings.


#include "TubboatsGameState.h"


#pragma region Core

ATubboatsGameState::ATubboatsGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATubboatsGameState::BeginPlay()
{
	Super::BeginPlay();
}

#pragma endregion

#pragma region Game State Functions

void ATubboatsGameState::EnterCurrentGameState()
{
	// End current timer if any
	if (ActiveGameTimerHandle.IsValid()) { GetWorldTimerManager().ClearTimer(ActiveGameTimerHandle); }

	// Switch based on current game state
	switch (CurrentGameState)
	{
	case ETubboatGameState::PreGame:
		GetWorldTimerManager().SetTimer(ActiveGameTimerHandle, this, &ATubboatsGameState::ExitCurrentGameState,
			PreGameDuration, false);
		
		break;

	case ETubboatGameState::Gameplay:
		GetWorldTimerManager().SetTimer(ActiveGameTimerHandle, this, &ATubboatsGameState::ExitCurrentGameState,
			GameDuration, false);

		break;

	case ETubboatGameState::GameEnd:
		GetWorldTimerManager().SetTimer(ActiveGameTimerHandle, this, &ATubboatsGameState::ExitCurrentGameState,
			GameEndDuration, false);

		break;
		
	default:
		break;
	}
}

void ATubboatsGameState::ExitCurrentGameState()
{
	switch (CurrentGameState)
	{
	case ETubboatGameState::PreGame:
		SetCurrentGameState(ETubboatGameState::Gameplay);
		break;

	case ETubboatGameState::Gameplay:
		SetCurrentGameState(ETubboatGameState::GameEnd);
		break;

	case ETubboatGameState::GameEnd:
		SetCurrentGameState(ETubboatGameState::Menu);
		break;
		
	default:
		break;
	}
}

#pragma endregion

#pragma region Setters

void ATubboatsGameState::SetCurrentGameState(const ETubboatGameState& InState)
{
	// Check if new game state is valid and not equal to current game state
	if (InState == CurrentGameState)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATubboatsGameState::SetGameState: New game state is equal to current game state"));
		return;
	}

	// Set new game state
	CurrentGameState = InState;

	// Change successful
	EnterCurrentGameState();
	BP_OnGameStateChanged(InState);
}

#pragma endregion

#pragma region Getters

float ATubboatsGameState::GetCurrentRemainingTime() const
{
	if (!ActiveGameTimerHandle.IsValid()) { return -1.f; }
	return GetWorldTimerManager().GetTimerRemaining(ActiveGameTimerHandle);
}

#pragma endregion