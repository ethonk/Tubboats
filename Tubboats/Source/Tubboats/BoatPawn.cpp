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

	/* Acceleration */   
	float fAvailableTorque = AccelerationCurve->GetFloatValue(fNormalisedSpeed) * fInputAxisForward * fMaxSpeed * 1; 
	FVector vAccelerationForce = GetActorForwardVector() * fAvailableTorque;
	vAccelerationForce = UKismetMathLibrary::ProjectVectorOnToPlane(vAccelerationForce,FVector::UpVector); // project into ground
	FVector vForceLocation =  GetActorLocation() + FVector(0,0,-5) + GetActorForwardVector() * 10; 
	MeshComp->AddForceAtLocation(vAccelerationForce, vForceLocation); 
	
	// Rotate
	if (fInputAxisForward<0) fCurrentSteeringAngle = -fCurrentSteeringAngle; 
	if (vWorldVelocity.SizeSquared() > 2) MeshComp->AddTorqueInDegrees(FVector(0,0,fCurrentSteeringAngle), NAME_None, true); 
}

void ABoatPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
 
}

void ABoatPawn::Move(const FVector2D& Value)
{
	FVector2d MovementVector = Value;

	fInputAxisForward = MovementVector.Y;
	fInputAxisRight = MovementVector.X;

	UE_LOG(LogTemp, Error, TEXT("MOVEEE!"));
	
} 

