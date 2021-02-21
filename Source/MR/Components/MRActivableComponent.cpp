// Fill out your copyright notice in the Description page of Project Settings.


#include "MRActivableComponent.h"

// Sets default values for this component's properties
UMRActivableComponent::UMRActivableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bCanBeActivated  = true;
}


void UMRActivableComponent::ActivateComponent(FGameplayTag Message /*= TEXT("")*/)
{
	if(bCanBeActivated)
	{
		OnActivated.Broadcast(Message);
	}
}