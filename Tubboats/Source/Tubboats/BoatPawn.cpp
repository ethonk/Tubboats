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
	RootComponent = MeshComp;

	// Guard against the default object
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		MeshComp->SetSimulatePhysics(false);
	}
}

// Called when the game starts or when spawned
void ABoatPawn::BeginPlay()
{
	Super::BeginPlay();

	// TODO Late Physics Setup
	if (MeshComp)
	{
		MeshComp->SetSimulatePhysics(true);
		MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); 

		// TODO: Crashes the build - MeshComp->SetMassOverrideInKg(NAME_None,50);
		MeshComp->BodyInstance.bOverrideMass = true;
		MeshComp->BodyInstance.SetMassOverride(50.f);
		// TODO: Crashes the build - MeshComp->SetCenterOfMass({0,0,-15});
		MeshComp->BodyInstance.COMNudge = {0,0,-35};
	}
		
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

void ABoatPawn::Move(const FVector2D& Value)
{
	FVector2d MovementVector = Value;

	fInputAxisForward = MovementVector.Y;
	fInputAxisRight = MovementVector.X; 

	// Speed
	FVector vWorldVelocity = MeshComp->GetPhysicsLinearVelocity(); 
	fSpeed = FVector::DotProduct(GetActorForwardVector(), vWorldVelocity);  
	
	// Steering  
	float fSteeringAngle = 45;
	fCurrentSteeringAngle = UKismetMathLibrary::MapRangeClamped(fInputAxisRight, -1, 1, fSteeringAngle*-1, fSteeringAngle); 
	
	// Torque
	if (fInputAxisForward<0) fCurrentSteeringAngle = -fCurrentSteeringAngle;  
	MeshComp->AddTorqueInDegrees(FVector(0,0,fCurrentSteeringAngle * 4), NAME_None, true); 
	
	// Brake
	FVector BrakeForce = FVector::ZeroVector;
	if ((fInputAxisForward < 0 && fSpeed > 0) ^ (fInputAxisForward > 0 &&  fSpeed < 0 )) BrakeForce = (vWorldVelocity * -1) * 1000;  
	
	// Acceleration
	float AccelerationConst = fInputAxisForward > 0 ? 80000 : 50000;
	FVector vForceLocation =  GetActorLocation() + FVector(0,0,-5) + GetActorForwardVector() * 10; 
	MeshComp->AddForceAtLocation(GetActorForwardVector() * AccelerationConst * fInputAxisForward + BrakeForce, vForceLocation );

	 
} 

