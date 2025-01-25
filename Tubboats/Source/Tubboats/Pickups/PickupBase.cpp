// Fill out your copyright notice in the Description page of Project Settings.


#include "../Pickups/PickupBase.h"

#include "Tubboats/BoatPawn.h"


#pragma region Core

APickupBase::APickupBase()
{
	// Create Components
	PickupCollision = CreateDefaultSubobject<USphereComponent>(TEXT("PickupCollision"));
	RootComponent = PickupCollision;
	//	- overlap only
	PickupCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	//	- starting radius
	PickupCollision->SetSphereRadius(400.0f);

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetupAttachment(PickupCollision);
	//	- no collision
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Bind Overlap Events
	PickupCollision->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnPickupOverlap);
}

void APickupBase::BeginPlay()
{
	Super::BeginPlay();

	// Despawn Timer
	GetWorld()->GetTimerManager().SetTimer(DespawnTimerHandle, this, &APickupBase::Despawn,
		DespawnDelay, false);
}

void APickupBase::Destroyed()
{
	Super::Destroyed();

	OnPickupDestroyed.Broadcast(this);
	OnPickupDestroyed.Clear();
}

#pragma endregion

#pragma region Collision

void APickupBase::OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check other actor is boat pawn
	if (!OtherActor || !OtherActor->IsA(ABoatPawn::StaticClass())) { return; }

	// Call Collision
	BP_OnPickup(OtherActor);

	// Destroy
	Destroy();
}

#pragma endregion

#pragma region Pickup Functions

void APickupBase::Despawn()
{
	Destroy();
}

#pragma endregion