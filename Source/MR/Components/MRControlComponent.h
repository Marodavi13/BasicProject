// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MRControlComponent.generated.h"

DECLARE_DELEGATE_OneParam(FMRInputEventDelegate, EInputEvent);

// This component handles all the input logic of the character
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MR_API UMRControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMRControlComponent();

	virtual void SetupInput(class UInputComponent* PlayerControllerInput);

protected:
	////////////////////////////////////////
   // Input Functions
   /// Movement
	void MoveForward(float Value);
	void MoveRight(float Value);

	///Orientation
	void Turn(float Value);
	void TurnRate(float Value);

	void LookUp(float Value);
	void LookUpRate(float Value);

	// Interaction
	void Interact();

	///Pause
	void Pause();
	void OpenInventory();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(Transient, SkipSerialization)
	class AMRCharacter* ControlledCharacter;
		
	// Controller orientation rates
	UPROPERTY(EditDefaultsOnly, Category = "Orientation")
	float BaseTurnRate;
	UPROPERTY(EditDefaultsOnly, Category = "Orientation")
	float BaseLookUpRate;

};
