// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Tubboats/Arsenal/PlayerOwnedActor.h"
#include "BoatCannonComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class TUBBOATS_API UBoatCannonComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

#pragma region Core
	
	UBoatCannonComponent();

	virtual void BeginPlay() override;

#pragma endregion

#pragma region Firing

	void FireAt(const FVector& FireLocation, const FRotator& OffsetRotation);

	UFUNCTION(BlueprintCallable)
	void FireLeft();

	UFUNCTION(BlueprintCallable)
	void FireRight();

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

	// Cannon
	
	UPROPERTY(EditDefaultsOnly, Category = "Properties|Cannon")
	FName LeftFirePointTag = "FirePoint_L";

	UPROPERTY(EditDefaultsOnly, Category = "Properties|Cannon")
	FName RightFirePointTag = "FirePoint_R";

	// Firing

	UPROPERTY(EditDefaultsOnly, Category = "Properties|Firing")
	TSubclassOf<APlayerOwnedActor> NeedleProjectileClass = nullptr;

#pragma endregion
	
};
