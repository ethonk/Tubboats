// Fill out your copyright notice in the Description page of Project Settings.


#include "BoatController.h" 
#include "BoatPawn.h"



ABoatController::ABoatController()
{
} 

void ABoatController::BeginPlay()
{
	Super::BeginPlay();

	Boat = Cast<ABoatPawn>(GetPawn());
}  