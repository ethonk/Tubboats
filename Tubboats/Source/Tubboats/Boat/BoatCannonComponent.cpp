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

	// Validate Owner
	
	if (!GetOwner()) { return; }

	// Get Fire Points
	
	TArray<UActorComponent*> TaggedLeftComponents = GetOwner()->GetComponentsByTag(USceneComponent::StaticClass(), LeftFirePointTag);
	if (!TaggedLeftComponents.IsEmpty()) { FirePointLeft = Cast<USceneComponent>(TaggedLeftComponents[0]); }
	
	TArray<UActorComponent*> TaggedRightComponents = GetOwner()->GetComponentsByTag(USceneComponent::StaticClass(), RightFirePointTag);
	if (!TaggedRightComponents.IsEmpty()) { FirePointRight = Cast<USceneComponent>(TaggedRightComponents[0]); }

	// Starting Ammo

	SetAmmo(MaxAmmo);
}

#pragma endregion

#pragma region Firing

void UBoatCannonComponent::FireAt(const FVector& FireLocation, const FRotator& OffsetRotation)
{
	// Validate
	
	if (!GetOwner() || !NeedleProjectileClass) { return; }

	// Fire Checking
	
	if (CurrentAmmo <= 0 || !bCanFire) { return; }

	// Ammo Management

	SetAmmo(CurrentAmmo - 1);

	// Fire Cooldown

	bCanFire = false;
	GetWorld()->GetTimerManager().SetTimer(FireCooldownTimer, this, &UBoatCannonComponent::ResetFire, FireCooldown, false);
	
	// Spawn the Needle
	
	const FTransform FireTransform = FTransform(OffsetRotation, FireLocation);
	APlayerOwnedActor* NewNeedle = GetWorld()->SpawnActor<APlayerOwnedActor>(NeedleProjectileClass, FireTransform);
	if (!NewNeedle) { return; }
	
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

void UBoatCannonComponent::ResetFire()
{
	bCanFire = true;
}

#pragma endregion

#pragma region Setters

void UBoatCannonComponent::SetAmmo(const int32 NewAmmo)
{
	CurrentAmmo = FMath::Clamp(NewAmmo, 0, MaxAmmo);
	OnAmmoCountChanged.Broadcast(CurrentAmmo);
}

#pragma endregion