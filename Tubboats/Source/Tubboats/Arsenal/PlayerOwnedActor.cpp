// Fill out your copyright notice in the Description page of Project Settings.


#include "../Arsenal/PlayerOwnedActor.h"


void APlayerOwnedActor::Initialize(APawn* InOwnerPlayerPawn)
{
	OwnerPlayerPawn = InOwnerPlayerPawn;
	BP_OnInitialize();
}