// Fill out your copyright notice in the Description page of Project Settings.

// core
#include "EnviromentManager.h"

// components
#include "Components/PostProcessComponent.h"


// Sets default values
AEnviromentManager::AEnviromentManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PostProcessComp = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcessComp")); 

	/* attachment hierarchy */ 
	PostProcessComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnviromentManager::BeginPlay()
{
	Super::BeginPlay();
	FPostProcessSettings PPSettings; 
	PPSettings.bOverride_DepthOfFieldFstop = true;
	PPSettings.bOverride_DepthOfFieldSensorWidth = true;
	PPSettings.bOverride_DepthOfFieldFocalDistance = true;
	PPSettings.DepthOfFieldFstop = 0.2;
	PPSettings.DepthOfFieldSensorWidth = 144;
	PPSettings.DepthOfFieldFocalDistance = 2000; 
	PostProcessComp->Settings = PPSettings; 
}

// Called every frame
void AEnviromentManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

