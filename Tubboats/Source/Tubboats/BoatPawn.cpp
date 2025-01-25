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
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); 
	MeshComp->SetMassOverrideInKg(NAME_None,50); 
	
	// attachment hierarchy
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void ABoatPawn::BeginPlay()
{
	Super::BeginPlay();

	// EnableInput(GetWorld()->GetFirstPlayerController());
	
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

}

void ABoatPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);  
}

void ABoatPawn::Move(const FVector2D& Value)
{
	FVector2d MovementVector = Value;

	fInputAxisForward = MovementVector.Y;
	fInputAxisRight = MovementVector.X;

	if (MovementVector.Y != 0)
	{
		fInputAxisRight = 0;
	}
	
	// // Speed
	// float fMaxSpeed = 1000;
	FVector vWorldVelocity = MeshComp->GetPhysicsLinearVelocity(); 
	// fSpeed = FVector::DotProduct(GetActorForwardVector(), vWorldVelocity);   
	// fNormalisedSpeed = FMath::Clamp(FMath::Abs(fSpeed) / fMaxSpeed, 0.f, 1.f);
	
	// Steering  
	float fSteeringAngle = 45;
	fCurrentSteeringAngle = UKismetMathLibrary::MapRangeClamped(fInputAxisRight, -1, 1, fSteeringAngle*-1, fSteeringAngle);

	
	// Rotate
	if (fInputAxisForward<0) fCurrentSteeringAngle = -fCurrentSteeringAngle; 
	// if (vWorldVelocity.SizeSquared() > 2)
	MeshComp->AddTorqueInDegrees(FVector(0,0,fCurrentSteeringAngle * 4), NAME_None, true); 
	
	/* Acceleration */   
	// float fAvailableTorque = fMaxSpeed; //AccelerationCurve->GetFloatValue(fNormalisedSpeed) * fInputAxisForward * fMaxSpeed * 1; 
	// FVector vAccelerationForce = GetActorForwardVector() * fAvailableTorque;
	// vAccelerationForce = UKismetMathLibrary::ProjectVectorOnToPlane(vAccelerationForce,FVector::UpVector); // project into ground
	// FVector vForceLocation =  GetActorLocation() + FVector(0,0,-5) + GetActorForwardVector() * 10; 
	// MeshComp->AddForceAtLocation(vAccelerationForce, GetActorLocation() ); 
	MeshComp->AddForce(GetActorForwardVector() * 50000 * fInputAxisForward);
} 

