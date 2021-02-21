// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "MRActivatorComponent.generated.h"


// This component can be used to activate the activable components of other actors (and itself)
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MR_API UMRActivatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMRActivatorComponent();

	// Call this function to activate all the activable actors
	UFUNCTION(BlueprintCallable)
	void ActivateActors();

	// Sets the message to be sent to this actors
	UFUNCTION(BlueprintCallable)
	void SetMessage(FGameplayTag NewMessage) { Message  = NewMessage;}

public:
	// Actors that will be activated when this component is activated
	UPROPERTY(EditInstanceOnly, Category = "Activation")
	TArray<AActor*> ActivableActors;

	// Message to send to the activable
	UPROPERTY(EditInstanceOnly, Category = "Activation")
	FGameplayTag Message;
};
