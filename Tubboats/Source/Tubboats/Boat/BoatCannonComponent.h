// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Tubboats/Arsenal/PlayerOwnedActor.h"
#include "BoatCannonComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAmmoCountChanged, int32, NewAmmoCount);

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

	void ResetFire();

#pragma endregion

#pragma region Setters

	UFUNCTION(BlueprintCallable)
	void SetAmmo(const int32 NewAmmo);

#pragma endregion
	
	//
	//
	//

#pragma region Delegates

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FAmmoCountChanged OnAmmoCountChanged;

#pragma endregion
	
#pragma region States

	// Firing

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "States|Firing")
	int32 CurrentAmmo = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "States|Firing")
	bool bCanFire = true;
	
	// Cannon
	
	UPROPERTY(EditDefaultsOnly, Category = "States|Cannon")
	USceneComponent* FirePointLeft = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "States|Cannon")
	USceneComponent* FirePointRight = nullptr;

	// Timers

	UPROPERTY(Transient)
	FTimerHandle FireCooldownTimer;
	
#pragma endregion
	
#pragma region Properties

	// Stats

	UPROPERTY(EditDefaultsOnly, Category = "Properties|Stats")
	float FireCooldown = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Properties|Stats")
	int32 MaxAmmo = 5;
	
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
