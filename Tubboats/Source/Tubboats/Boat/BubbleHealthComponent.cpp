// Fill out your copyright notice in the Description page of Project Settings.


#include "../Boat/BubbleHealthComponent.h"


#pragma region Core

void UBubbleHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// Try get owner
	if (!GetOwner()) { return; }

	// From owner, attempt to get all actors with type APlayerBubble
	TArray<AActor*> AttachedBubbleActors;
	GetOwner()->GetAttachedActors(AttachedBubbleActors);
	// Get all bubbles
	for (AActor* AttachedActor : AttachedBubbleActors)
	{
		if (APlayerBubble* Bubble = Cast<APlayerBubble>(AttachedActor))
		{
			PlayerBubbles.Add(Bubble);
			Bubble->OnBubbleActivityChanged.AddDynamic(this, &UBubbleHealthComponent::BubbleActivityChanged);
		}
	}
}

#pragma endregion

#pragma region Bubble Management

void UBubbleHealthComponent::BubbleActivityChanged(const bool bLastWasActive)
{
	if (bLastWasActive) { return; }

	// Check if all bubbles are popped
	for (const APlayerBubble* Bubble : PlayerBubbles)
	{
		if (Bubble->bActivated) { return; }
	}

	// If all bubbles are popped, broadcast event
	BP_AllBubblesPopped();
}

#pragma endregion