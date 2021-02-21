// Copyright Epic Games, Inc. All Rights Reserved.

#include "MRCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "MR/Components/MRAbilityComponent.h"
#include "MR/Components/MRDetectionComponent.h"
#include "MR/Components/MRControlComponent.h"
DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AMRCharacter

AMRCharacter::AMRCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	CameraComponent->bUsePawnControlRotation = true;

	ControlComponent = CreateDefaultSubobject<UMRControlComponent>(TEXT("ControlComponent"));
	AbilityComponent = CreateDefaultSubobject<UMRAbilityComponent>(TEXT("AbilityComponent"));
}

void AMRCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	// Detection component wasn't being added to the character in BPs for some reason, so I had to use this function
	DetectionComponent = FindComponentByClass<UMRDetectionComponent>();
	check(DetectionComponent);
}

void AMRCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMRCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent && ControlComponent);

	ControlComponent->SetupInput(PlayerInputComponent);
}

