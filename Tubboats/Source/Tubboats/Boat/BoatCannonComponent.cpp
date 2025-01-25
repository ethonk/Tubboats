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

	// Get Left Fire Point
	TArray<UActorComponent*> TaggedLeftComponents = GetOwner()->GetComponentsByTag(USceneComponent::StaticClass(), LeftFirePointTag);
	if (!TaggedLeftComponents.IsEmpty()) { FirePointLeft = Cast<USceneComponent>(TaggedLeftComponents[0]); }

	// Get Right Fire Point
	TArray<UActorComponent*> TaggedRightComponents = GetOwner()->GetComponentsByTag(USceneComponent::StaticClass(), RightFirePointTag);
	if (!TaggedRightComponents.IsEmpty()) { FirePointRight = Cast<USceneComponent>(TaggedRightComponents[0]); }

	// TODO Validate Fire Points
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

void UBoatCannonComponent::FireAt(const FVector& FireLocation, const FRotator& OffsetRotation)
{
	if (!GetOwner() || !NeedleProjectileClass) { return; }

	// Make Spawn Transform

	// Spawn the Needle
	const FTransform FireTransform = FTransform(OffsetRotation, FireLocation);
	APlayerOwnedActor* NewNeedle = GetWorld()->SpawnActor<APlayerOwnedActor>(NeedleProjectileClass, FireTransform);
	if (!NewNeedle) { return; }

	// Setup Needle
	NewNeedle->Initialize(Cast<APawn>(GetOwner()));
}

void UBoatCannonComponent::FireLeft()
{
	if (!FirePointLeft) { return; }

	// Get actor rotation and zero out pitch and roll
	FRotator FireRotation = FirePointLeft->GetComponentRotation();
	FireRotation.Pitch = 0;
	FireRotation.Roll = 0;

	// Fire
	FireAt(FirePointLeft->GetComponentLocation(), FireRotation);
}

void UBoatCannonComponent::FireRight()
{
	if (!FirePointRight) { return; }

	// Get actor rotation and zero out pitch and roll
	FRotator FireRotation = FirePointRight->GetComponentRotation();
	FireRotation.Pitch = 0;
	FireRotation.Roll = 0;

	// Fire
	FireAt(FirePointRight->GetComponentLocation(), FireRotation);
}

#pragma endregion