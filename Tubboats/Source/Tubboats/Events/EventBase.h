// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EventBase.generated.h"

UCLASS()
class TUBBOATS_API AEventBase : public AActor
{
	GENERATED_BODY()
	
public:	

#pragma region Core

	AEventBase();

	virtual void BeginPlay() override;
	
#pragma endregion

#pragma region Collision
	
	UFUNCTION()
	void OnEventMeshBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

#pragma endregion

#pragma region Event Functions

	UFUNCTION()
	void EventEnded();

#pragma endregion
	
#pragma region Responders

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_EventStarted();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_EventEnded();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_EventHitActor(AActor* HitActor);

#pragma endregion
	
	//
	//
	//

#pragma region Components

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* EventRoot = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* EventMesh = nullptr;

#pragma endregion

#pragma region States

	// Timers

	UPROPERTY(Transient)
	FTimerHandle EventDestroyTimerHandle;

#pragma endregion

#pragma region Properties

	// Duration
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Duration")
	float EventDuration = 10.0f;

#pragma endregion
	
};
