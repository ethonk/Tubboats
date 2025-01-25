// Fill out your copyright notice in the Description page of Project Settings.


#include "TubboatsGameState.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Tubboats/BoatPawn.h"


#pragma region Core

ATubboatsGameState::ATubboatsGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATubboatsGameState::BeginPlay()
{
	Super::BeginPlay();

	PopulateSpawnLocations();
}

#pragma endregion

#pragma region Game State Functions

// Game State

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

		SpawnAllPlayers();

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
		DestroyAllPlayers();
		SetCurrentGameState(ETubboatGameState::Menu);
		
		break;
		
	default:
		break;
	}
}

// Players

void ATubboatsGameState::SpawnAllPlayers()
{
	for (const FVector& Location : FoundSpawnLocations)
	{
		// Spawn player
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		// Catalogue Player
		APawn* NewPlayer = GetWorld()->SpawnActor<APawn>(PlayerClassToSpawn, Location, FRotator::ZeroRotator, SpawnParams);
		if (!NewPlayer) { continue; }

		// Set index of Boat Pawn
		if (ABoatPawn* NewBoat = Cast<ABoatPawn>(NewPlayer)) { NewBoat->PlayerIndex = ActivePlayers.Num(); }
		
		// Add to active players
		ActivePlayers.Add(NewPlayer);
	}
}

void ATubboatsGameState::DestroyAllPlayers()
{
	ActivePlayers.Empty();
	
	// Find all BoatPawns and destroy them
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABoatPawn::StaticClass(), FoundActors);
	for (AActor* Actor : FoundActors) { Actor->Destroy(); }
}

void ATubboatsGameState::PlayerDied(APawn* DyingPlayer)
{
	if (!DyingPlayer) { return; }

	// Remove from active players
	ActivePlayers.Remove(DyingPlayer);

	// Do a funny (add random impulse to player pawn mostly going high)
	if (const ABoatPawn* DyingBoat = Cast<ABoatPawn>(DyingPlayer))
	{
		DyingBoat->MeshComp->AddImpulse(FVector(0.f, 0.f, 7000.f), NAME_None, true);
	}

	// Check if one player remains
	if (ActivePlayers.Num() <= 1 && CurrentGameState == ETubboatGameState::Gameplay)
	{
		SetCurrentGameState(ETubboatGameState::GameEnd);
	}
}

#pragma endregion

#pragma region Helpers

void ATubboatsGameState::PopulateSpawnLocations()
{
	// Get all tagged actors
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), SpawnLocationsTag, FoundActors);

	// Iterate, add
	for (const AActor* Actor : FoundActors) { FoundSpawnLocations.Add(Actor->GetActorLocation()); }
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