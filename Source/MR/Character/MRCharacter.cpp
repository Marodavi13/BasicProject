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

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	ArmsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	ArmsMesh->SetOnlyOwnerSee(true);
	ArmsMesh->SetupAttachment(CameraComponent);
	ArmsMesh->bCastDynamicShadow = false;
	ArmsMesh->CastShadow = false;
	ArmsMesh->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	ArmsMesh->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	ControlComponent = CreateDefaultSubobject<UMRControlComponent>(TEXT("ControlComponent"));
	AbilityComponent = CreateDefaultSubobject<UMRAbilityComponent>(TEXT("AbilityComponent"));
	//DetectionComponent = CreateDefaultSubobject<UMRDetectionComponent>(TEXT("DetectionComponent"));
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

