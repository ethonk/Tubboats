// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h" 

#include "BoatPawn.generated.h"

UCLASS()
class TUBBOATS_API ABoatPawn : public APawn
{
	GENERATED_BODY()

private:
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* AccelerationCurve; // determines acceleration   
	
	/// <summary>
	/// Input variables
	/// </summary>
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fInputAxisForward; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fInputAxisRight; 
	
	/// <summary>
	/// Movement checks
	/// </summary>
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fCurrentSteeringAngle;

	/// <summary>
	/// Speed of the vehicle
	/// </summary>
	UPROPERTY(VisibleAnywhere)
	float fSpeed{0};

	/// <summary>
	/// Normalised speed of the vehicle
	/// </summary>
	UPROPERTY(VisibleAnywhere)
	float fNormalisedSpeed{0}; 

	/// <summary>
	/// Exposed Components
	/// </summary>

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MeshComp; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Sets default values for this pawn's properties
	ABoatPawn();  
	
	/// <summary>
	/// Runs the update function for physics
	/// </summary> 
	virtual void Tick(float DeltaTime) override; 
  
	// /// <summary>
	// /// Sets up components 
	// /// </summary> 
	// virtual void PostInitializeComponents() override;   


	
	/// <summary>
	/// Getters
	/// </summary>

	UFUNCTION(BlueprintCallable)
	float GetNormalisedSpeed() const { return fNormalisedSpeed; }

};
