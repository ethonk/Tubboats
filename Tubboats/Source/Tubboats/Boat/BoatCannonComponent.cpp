// Fill out your copyright notice in the Description page of Project Settings.


#include "../Boat/BoatCannonComponent.h"


#pragma region Core

UBoatCannonComponent::UBoatCannonComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBoatCannonComponent::BeginPlay()
{
	Super::BeginPlay();

	// Check Owner
	if (!GetOwner()) { return; }

	// Get Fire Points
	FirePointLeft = GetOwner()->FindComponentByClass<USceneComponent>();
	FirePointRight = GetOwner()->FindComponentByClass<USceneComponent>();

	// TODO Log
	if (!FirePointLeft || !FirePointRight)
	{
		UE_LOG(LogTemp, Error, TEXT("Fire Points not found!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Fire Points found!"));
	}
}

#pragma endregion

#pragma region Firing

void UBoatCannonComponent::FireAt(const FVector& FireLocation)
{
	// Debug point to fire at
	DrawDebugPoint(GetWorld(), FireLocation, 10, FColor::Yellow, true);
	UE_LOG(LogTemp, Warning, TEXT("She gets 5 big booms at %s"), *FireLocation.ToString());
}

void UBoatCannonComponent::FireLeft()
{
	if (!FirePointLeft) { return; }
	FireAt(FirePointLeft->GetComponentLocation());
}

void UBoatCannonComponent::FireRight()
{
	if (!FirePointRight) { return; }
	FireAt(FirePointRight->GetComponentLocation());
}

#pragma endregion