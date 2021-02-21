// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "MRAbilityComponent.generated.h"

class UMRAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityStarted, UMRAbility*, Ability);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityEnded, UMRAbility*, Ability);


// This component handles the behavior and interaction between different abilities
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MR_API UMRAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMRAbilityComponent();


	// Checks if it can perform the ability and performs it
	UFUNCTION(BlueprintCallable)
	bool TryToPerformAbility(FGameplayTag AbilityTag);
	
	// Stops an ability by its tag
	UFUNCTION(BlueprintCallable)
	void StopAbility(FGameplayTag AbilityTag);

	// Stops the ability being done right now
	UFUNCTION(BlueprintCallable)
	void StopCurrentAbility();

	//Returns the active ability
	UFUNCTION(BlueprintCallable)
	UMRAbility* GetCurrentAbility()  const { return CurrentAbility; }

	// Returns an ability based on its tag
	UFUNCTION(BlueprintCallable)
	UMRAbility* GetAbilityByTag(const FGameplayTag& AbilityTag) const;

	virtual void InitializeComponent() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Performs the Ability 
	void PerformAbility(UMRAbility* Ability);
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
	// EVENTS
	UPROPERTY(BlueprintAssignable)
	FOnAbilityStarted OnAbilityStarted;

	UPROPERTY(BlueprintAssignable)
	FOnAbilityEnded OnAbilityEnded;

protected:
	// The classes of the abilities
	UPROPERTY(EditAnywhere)
	TSet<TSubclassOf<UMRAbility>> AbilityClasses;

	// References to the abilities
	UPROPERTY(Transient, SkipSerialization)
	TSet<UMRAbility*> Abilities;

	// The active ability
	UPROPERTY(Transient, SkipSerialization)
	UMRAbility* CurrentAbility;
};
