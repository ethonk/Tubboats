// Fill out your copyright notice in the Description page of Project Settings.


#include "BoatController.h" 
#include "BoatPawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"



ABoatController::ABoatController()
{
} 

void ABoatController::BeginPlay()
{
	Super::BeginPlay();

	Boat = Cast<ABoatPawn>(GetPawn()); 
	 
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =  ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
	{
		// Ensure you have a valid mapping context
		if (InputMappingContext) {
			Subsystem->AddMappingContext(InputMappingContext, 0);
			UE_LOG(LogTemp, Error, TEXT("Input Mapping Context added!"));
		}
	} 
}

void ABoatController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABoatController::Move);
		UE_LOG(LogTemp, Error, TEXT("MoveAction bound successfully!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("EnhancedInputComponent not found!"));
	}
}

void ABoatController::Move(const FInputActionValue& Value)
{
	FVector2d MovementVector = Value.Get<FVector2d>();

	Boat->fInputAxisForward = MovementVector.Y;
	Boat->fInputAxisRight = MovementVector.X;

	UE_LOG(LogTemp, Error, TEXT("MOVEEE!"));
}  