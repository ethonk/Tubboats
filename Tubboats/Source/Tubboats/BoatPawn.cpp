// Fill out your copyright notice in the Description page of Project Settings.


#include "BoatPawn.h"

// Sets default values
ABoatPawn::ABoatPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; 

	// MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));   
	// BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent")); 
	// BoxComp->SetBoxExtent(FVector(100.0f, 60.0f, 25.0f));
}

// Called when the game starts or when spawned
void ABoatPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoatPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABoatPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABoatPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ABoatPawn::AttachWheels()
{
}

