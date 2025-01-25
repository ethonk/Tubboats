// Fill out your copyright notice in the Description page of Project Settings.

// core
#include "BoatPawn.h"


#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"



// Sets default values
ABoatPawn::ABoatPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; 

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetMassOverrideInKg(NAME_None,50); 
	
	// attachment hierarchy
	RootComponent = MeshComp;

}

// Called when the game starts or when spawned
void ABoatPawn::BeginPlay()
{
	Super::BeginPlay();

	EnableInput(GetWorld()->GetFirstPlayerController());
	
	// Get the PlayerController and add the input mapping context
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			// Ensure you have a valid mapping context
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
				UE_LOG(LogTemp, Error, TEXT("Input Mapping Context added!"));
			}
		}
	}
}

// Called every frame
void ABoatPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Speed
	float fMaxSpeed = 15000;
	FVector vWorldVelocity = MeshComp->GetPhysicsLinearVelocity(); 
	fSpeed = FVector::DotProduct(GetActorForwardVector(), vWorldVelocity);   
	fNormalisedSpeed = FMath::Clamp(FMath::Abs(fSpeed) / fMaxSpeed, 0.f, 1.f);
	
	// Steering  
	float fSteeringAngle = 45;
	fCurrentSteeringAngle = UKismetMathLibrary::MapRangeClamped(fInputAxisRight, -1, 1, fSteeringAngle*-1, fSteeringAngle);
	
	// Rotate
	if (fInputAxisForward<0) fCurrentSteeringAngle = -fCurrentSteeringAngle; 
	if (vWorldVelocity.SizeSquared() > 2) MeshComp->AddTorqueInDegrees(FVector(0,0,fCurrentSteeringAngle), NAME_None, true); 
}

void ABoatPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); 

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABoatPawn::Move);
		UE_LOG(LogTemp, Warning, TEXT("MoveAction bound successfully!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("EnhancedInputComponent not found!"));
	}
}

void ABoatPawn::Move(const FInputActionValue& Value)
{
	FVector2d MovementVector = Value.Get<FVector2d>();

	fInputAxisForward = MovementVector.Y;
	fInputAxisRight = MovementVector.X;

	UE_LOG(LogTemp, Error, TEXT("MOVEEE!"));
} 

