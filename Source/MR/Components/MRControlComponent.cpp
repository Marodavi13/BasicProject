// Fill out your copyright notice in the Description page of Project Settings.


#include "MRControlComponent.h"
#include "MR/Character/MRCharacter.h"
#include "MR/MR.h"
#include "MRDetectionComponent.h"

// Sets default values for this component's properties
UMRControlComponent::UMRControlComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	// ...
}


void UMRControlComponent::MoveForward(float Value)
{
	ControlledCharacter->AddMovementInput(ControlledCharacter->GetActorForwardVector(), Value);
}

void UMRControlComponent::MoveRight(float Value)
{
	ControlledCharacter->AddMovementInput(ControlledCharacter->GetActorRightVector(), Value);

}

void UMRControlComponent::Turn(float Value)
{
	ControlledCharacter->AddControllerYawInput(Value);
}

void UMRControlComponent::TurnRate(float Value)
{
	ControlledCharacter->AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void UMRControlComponent::LookUp(float Value)
{
	ControlledCharacter->AddControllerPitchInput(Value);
}

void UMRControlComponent::LookUpRate(float Value)
{
	ControlledCharacter->AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void UMRControlComponent::Interact()
{
	UMRDetectionComponent* Detection = ControlledCharacter->FindComponentByClass<UMRDetectionComponent>();
	if (Detection)
	{
		Detection->Interact();
	}
}

void UMRControlComponent::Pause()
{
	//todo
}

void UMRControlComponent::OpenInventory()
{
	//todo
}

// Called when the game starts
void UMRControlComponent::BeginPlay()
{
	Super::BeginPlay();
	ControlledCharacter = GetOwner<AMRCharacter>();
	checkf(ControlledCharacter, TEXT("Character not found"));

}


// Called every frame
void UMRControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMRControlComponent::SetupInput(UInputComponent* PlayerControllerInput)
{
	// Movement
	PlayerControllerInput->BindAxis(MRInputTags::MoveForward, this, &UMRControlComponent::MoveForward);
	PlayerControllerInput->BindAxis(MRInputTags::MoveRight, this, &UMRControlComponent::MoveRight);

	// Orientation
	// Rate for controllers
	PlayerControllerInput->BindAxis(MRInputTags::Turn, this, &UMRControlComponent::Turn);
	PlayerControllerInput->BindAxis(MRInputTags::TurnRate, this, &UMRControlComponent::TurnRate);
	PlayerControllerInput->BindAxis(MRInputTags::LookUp, this, &UMRControlComponent::LookUp);
	PlayerControllerInput->BindAxis(MRInputTags::LookUpRate, this, &UMRControlComponent::LookUpRate);

	PlayerControllerInput->BindAction(MRInputTags::Interact, EInputEvent::IE_Pressed,this, &UMRControlComponent::Interact);
}
