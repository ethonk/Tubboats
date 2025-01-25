// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerOwnedActor.h"
#include "PlayerBubble.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBubbleActivityChanged, bool, IsActive);

UCLASS()
class TUBBOATS_API APlayerBubble : public APlayerOwnedActor
{
	GENERATED_BODY()
	
public:

#pragma region Core

	virtual void BeginPlay() override;

#pragma endregion

#pragma region Setters

	UFUNCTION(BlueprintCallable)
	void SetActivated(bool bNewActivated);

#pragma endregion
	
	//
	//
	//

#pragma region Delegates

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnBubbleActivityChanged OnBubbleActivityChanged;

#pragma endregion

#pragma region States

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "States")
	bool bActivated = true;;

#pragma endregion

};
