// Fill out your copyright notice in the Description page of Project Settings.


#include "../Arsenal/PlayerBubble.h"


#pragma region Core

void APlayerBubble::BeginPlay()
{
	Super::BeginPlay();
	SetActivated(bActivated);
}

#pragma endregion

#pragma region Setters

void APlayerBubble::SetActivated(const bool bNewActivated)
{
	bActivated = bNewActivated;
	OnBubbleActivityChanged.Broadcast(bActivated);
}

#pragma endregion