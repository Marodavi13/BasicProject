// Fill out your copyright notice in the Description page of Project Settings.


#include "MRActivatorComponent.h"
#include "MRActivableComponent.h"

// Sets default values for this component's properties
UMRActivatorComponent::UMRActivatorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UMRActivatorComponent::ActivateActors()
{
	// Activate all referenced actors
	for (AActor* Actor : ActivableActors)
	{
		if (IsValid(Actor))
		{
			UMRActivableComponent* ActivableComponent = Actor->FindComponentByClass<UMRActivableComponent>();
			if (ActivableComponent)
			{
				ActivableComponent->ActivateComponent(Message);
			}
		}
	}
}

