// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "PickupBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPickupDestroyed, APickupBase*, Pickup);


UCLASS()
class TUBBOATS_API APickupBase : public AActor
{
	GENERATED_BODY()

public:	

#pragma region Core
	
	APickupBase();

	virtual void BeginPlay() override;

	virtual void Destroyed() override;
	
#pragma endregion

#pragma region Collision

	UFUNCTION()
	void OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

#pragma endregion

#pragma region Pickup Functions

	void Despawn();
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnPickup(AActor* OtherActor);

#pragma endregion
	
	//
	//
	//

#pragma region Delegates

	UPROPERTY(BlueprintAssignable)
	FPickupDestroyed OnPickupDestroyed;
	
#pragma endregion
	
#pragma region Components

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* PickupCollision = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* PickupMesh = nullptr;

#pragma endregion

#pragma region States

	UPROPERTY(Transient)
	FTimerHandle DespawnTimerHandle;

#pragma endregion

#pragma region Properties

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Properties|Spawning")
	float DespawnDelay = 13.f;

#pragma endregion

};
