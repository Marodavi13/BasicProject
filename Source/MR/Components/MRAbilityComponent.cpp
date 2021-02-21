// Fill out your copyright notice in the Description page of Project Settings.

#include "MRAbilityComponent.h"
#include "../Abilities/MRAbility.h"

// Sets default values for this component's properties
UMRAbilityComponent::UMRAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

}


// Called when the game starts
void UMRAbilityComponent::BeginPlay()
{
	Super::BeginPlay();


}

UMRAbility* UMRAbilityComponent::GetAbilityByTag(const FGameplayTag& AbilityTag) const
{
	UMRAbility* ReturnedAbility = nullptr;

	// Traverse all the TSet and find the ability that has the same Tag
	for (UMRAbility* Ability : Abilities)
	{
		if (Ability->AbilityTag == AbilityTag)
		{
			ReturnedAbility = Ability;
			break;
		}
	}

	return ReturnedAbility;
}


void UMRAbilityComponent::InitializeComponent()
{
	Super::InitializeComponent();
	for (TSubclassOf<UMRAbility> AbilityClass : AbilityClasses)
	{
		// Create the ability
		UMRAbility* NewAbility = NewObject<UMRAbility>(this, AbilityClass);

		// check if the ability is valid
		check(NewAbility->AbilityTag.IsValid());

		// Initialize the Ability
		NewAbility->InitializeAbility(GetOwner<AMRCharacter>());

		//Add the ability to the TSet
		Abilities.Add(NewAbility);
	}
}

bool UMRAbilityComponent::TryToPerformAbility(FGameplayTag AbilityTag)
{
	bool bHasBeenPerformed = false;
	//If I am not doing other Ability
  	if (!CurrentAbility)
	{
		UMRAbility* AbilityToPerform = GetAbilityByTag(AbilityTag);
		// If I can perform the ability with that tag
		if (AbilityToPerform && AbilityToPerform->CanPerformAbility())
		{
			//Activate this ability
			PerformAbility(AbilityToPerform);
			bHasBeenPerformed = true;
		}
	}

	return bHasBeenPerformed;
}

void UMRAbilityComponent::StopAbility(FGameplayTag AbilityTag)
{
	if(CurrentAbility)
	{ 
		UMRAbility* AbilityToStop = GetAbilityByTag(AbilityTag);
		if (CurrentAbility == AbilityToStop)
		{
			StopCurrentAbility();
		}
	}
}


void UMRAbilityComponent::PerformAbility(UMRAbility* Ability)
{
	// If the Ability exists, activate and cache it
	if (Ability)
	{
		Ability->ActivateAbility();
		CurrentAbility = Ability;
		OnAbilityStarted.Broadcast(Ability);
	}
}


void UMRAbilityComponent::StopCurrentAbility()
{
	// If the Ability exists, deactivate it and clear the references
	if (CurrentAbility)
	{
		CurrentAbility->DeactivateAbility();
		UMRAbility* EndedAbility = CurrentAbility;
		CurrentAbility = nullptr;
		OnAbilityEnded.Broadcast(EndedAbility);
	}
}

// Called every frame
void UMRAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentAbility)
	{
		CurrentAbility->UpdateAbility(DeltaTime);
	}
}

