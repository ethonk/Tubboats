// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Tubboats/Arsenal/PlayerBubble.h"
#include "BubbleHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class TUBBOATS_API UBubbleHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

#pragma region Core
	
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Bubble Management

	UFUNCTION()
	void BubbleActivityChanged(const bool bLastWasActive);

	UFUNCTION(BlueprintImplementableEvent, Category = "Bubble Management")
	void BP_AllBubblesPopped();

#pragma endregion

	//
	//
	//

#pragma region States

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "States")
	TArray<APlayerBubble*> PlayerBubbles;

#pragma endregion
		
};
