// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnviromentManager.generated.h"

UCLASS()
class TUBBOATS_API AEnviromentManager : public AActor
{
	GENERATED_BODY()

public:
	/// <summary>
	/// Exposed Components
	/// </summary>
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComp{nullptr};
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPostProcessComponent* PostProcessComp{nullptr};



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; 
	
public:	
	// Sets default values for this actor's properties
	AEnviromentManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override; 

};
