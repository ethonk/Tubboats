// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerOwnedActor.generated.h"

UCLASS()
class TUBBOATS_API APlayerOwnedActor : public AActor
{
	GENERATED_BODY()
	
public:

	void Initialize(APawn* InOwnerPlayerPawn);
	UFUNCTION(BlueprintImplementableEvent, Category = "Game State")
	void BP_OnInitialize();
	
	//
	//
	//

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "States")
	APawn* OwnerPlayerPawn = nullptr;

};
