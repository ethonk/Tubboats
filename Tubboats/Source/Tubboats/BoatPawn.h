// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "Boat/BoatCannonComponent.h"
#include "GameFramework/Pawn.h" 

#include "BoatPawn.generated.h"

UCLASS()
class TUBBOATS_API ABoatPawn : public APawn
{
	GENERATED_BODY()

private:
	

public:

#pragma region Components

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoatCannonComponent* CannonComponent;

#pragma endregion

#pragma region States

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
	int PlayerIndex = 0;

#pragma endregion
	
	/// <summary>
	/// Input Actions
	/// </summary>
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* AccelerationCurve; // determines acceleration  

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Sets default values for this pawn's properties
	ABoatPawn();     

	// Called for movement input
	UFUNCTION(BlueprintCallable)
	void Move(const FVector2D& Value);
	
	/// <summary>
	/// Getters
	/// </summary>

	UFUNCTION(BlueprintCallable)
	float GetNormalisedSpeed() const { return fNormalisedSpeed; }

};
