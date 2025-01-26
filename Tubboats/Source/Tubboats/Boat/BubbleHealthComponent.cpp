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
	// Get bubble count
	int32 ActiveBubbleCount = 0;
	for (const APlayerBubble* Bubble : PlayerBubbles) { if (Bubble->bActivated) { ++ActiveBubbleCount; } }
	
	// Broadcast event
	BP_BubbleCountChanged(ActiveBubbleCount);
	
	// Below, only check for game over.
	
	if (bLastWasActive) { return; }

	// Check if all bubbles are popped
	for (const APlayerBubble* Bubble : PlayerBubbles)
	{
		if (Bubble->bActivated) { return; }
	}

	// If all bubbles are popped, broadcast event
	BP_AllBubblesPopped();
}

void UBubbleHealthComponent::RestoreClosestBubble(const FVector& Location)
{
	// Get all bubbles that are not active
	TArray<APlayerBubble*> InactiveBubbles;
	for (APlayerBubble* Bubble : PlayerBubbles) { if (Bubble && !Bubble->bActivated) { InactiveBubbles.Add(Bubble); } }

	// If no inactive bubbles, return
	if (InactiveBubbles.Num() == 0) { return; }

	// Find the closest bubble
	APlayerBubble* ClosestBubble = nullptr;
	float ClosestDistance = TNumericLimits<float>::Max();
	for (APlayerBubble* Bubble : InactiveBubbles)
	{
		const float Distance = FVector::Dist(Bubble->GetActorLocation(), Location);
		if (Distance < ClosestDistance)
		{
			ClosestBubble = Bubble;
			ClosestDistance = Distance;
		}
	}

	// Validate
	if (!ClosestBubble) { return; }

	// Activate the closest bubble
	ClosestBubble->SetActivated(true);
}

#pragma endregion