// Fill out your copyright notice in the Description page of Project Settings.

// core
#include "EnviromentManager.h"

// components
#include "Components/PostProcessComponent.h" 
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AEnviromentManager::AEnviromentManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PostProcessComp = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcessComp"));

	// SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	// SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	// SpringArm->TargetArmLength = 2000.0f;
	// SpringArm->bInheritYaw = false;
	// SpringArm->bInheritPitch = false;
	// SpringArm->bInheritRoll = false;
	// SpringArm->bDoCollisionTest = false;
// 
	// CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	// CameraComp->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
// 
	// // attachment hierarchy
	RootComponent = PostProcessComp;
	// SpringArm->SetupAttachment(RootComponent);
	// CameraComp->SetupAttachment(SpringArm); 
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
	
    // FViewTargetTransitionParams TransitionParams;
    // TransitionParams.BlendTime = BlendTime;
    // TransitionParams.BlendFunction = BlendFunction;
    // TransitionParams.BlendExp = BlendExp;

    // PlayerController->SetViewTarget(NewCamera, TransitionParams);
}

// Called every frame
void AEnviromentManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

