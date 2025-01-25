// Fill out your copyright notice in the Description page of Project Settings.


#include "../Events/EventBase.h"


#pragma region Core

AEventBase::AEventBase()
{
	// Setup Root
	EventRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Event Root"));
	RootComponent = EventRoot;
	
 	// Create Mesh
	EventMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Event Mesh"));
	EventMesh->SetupAttachment(RootComponent);
	EventMesh->OnComponentBeginOverlap.AddDynamic(this, &AEventBase::OnEventMeshBeginOverlap);
}

void AEventBase::BeginPlay()
{
	Super::BeginPlay();

	// Timer
	GetWorld()->GetTimerManager().SetTimer(EventDestroyTimerHandle, this, &AEventBase::EventEnded,
		EventDuration, false);

	// Notify
	BP_EventStarted();
}

#pragma endregion

#pragma region Collision

void AEventBase::OnEventMeshBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check valid
	if (!OtherActor) { return; }

	// Notify
	BP_EventHitActor(OtherActor);
}

#pragma endregion

#pragma region Event Functions

void AEventBase::EventEnded()
{
	// Notify
	BP_EventEnded();

	// Destroy
	Destroy();
}

#pragma endregion