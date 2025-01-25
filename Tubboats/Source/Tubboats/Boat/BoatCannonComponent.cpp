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