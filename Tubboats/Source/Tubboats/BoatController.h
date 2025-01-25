// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h" 


#include "InputMappingContext.h"
#include "BoatController.generated.h"


/**
 * 
 */
UCLASS()
class TUBBOATS_API ABoatController : public APlayerController
{
	GENERATED_BODY()

public:

	/// <summary>
	/// Input Actions
	/// </summary>
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ABoatPawn* Boat;
	
	
public:
	ABoatController(); 
	
	virtual void BeginPlay() override;

	virtual  void SetupInputComponent() override;

	// Called for movement input 
	void Move(const FInputActionValue& Value);
};
