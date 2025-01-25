// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BoatCannonComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TUBBOATS_API UBoatCannonComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

#pragma region Core
	
	UBoatCannonComponent();

	virtual void BeginPlay() override;

#pragma endregion

	//
	//
	//

#pragma region States

	UPROPERTY(EditDefaultsOnly, Category = "States|Cannon")
	USceneComponent* FirePointLeft = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "States|Cannon")
	USceneComponent* FirePointRight = nullptr;
	
#pragma endregion
	
#pragma region Properties

	UPROPERTY(EditDefaultsOnly, Category = "Properties|Cannon")
	FString LeftFirePointTag = "FirePoint_L";

	UPROPERTY(EditDefaultsOnly, Category = "Properties|Cannon")
	FString RightFirePointTag = "FirePoint_R";

#pragma endregion
	
};
