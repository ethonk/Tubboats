// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h" 



#include "BoatController.generated.h"


/**
 * 
 */
UCLASS()
class TUBBOATS_API ABoatController : public APlayerController
{
	GENERATED_BODY()

public:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ABoatPawn* Boat; 
	
public:
	ABoatController(); 
	
	virtual void BeginPlay() override;  
};
