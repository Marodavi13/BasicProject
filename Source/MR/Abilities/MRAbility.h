// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MR/Character/MRCharacter.h"
#include "GameplayTagContainer.h"
#include "MRAbility.generated.h"

//Basic Ability handled by the Ability Component
UCLASS(Blueprintable)
class MR_API UMRAbility : public UObject
{
	GENERATED_BODY()
public:

	// Tag of the ability, can't be null
	UPROPERTY(EditDefaultsOnly, Category = Tag)
	FGameplayTag AbilityTag;

	UFUNCTION(BlueprintNativeEvent)
	void InitializeAbility(AMRCharacter* Owner);
	virtual void InitializeAbility_Implementation(AMRCharacter* Owner);

	// Checks the conditions to perform the ability
	UFUNCTION(BlueprintNativeEvent)
	bool CanPerformAbility();
	virtual bool CanPerformAbility_Implementation() const;

	// Activates the ability and does the functionality needed at the start of the ability
	UFUNCTION(BlueprintNativeEvent)
	void ActivateAbility();
	virtual void ActivateAbility_Implementation(){}

	// Deactivates the ability and does the functionality needed at the end of the ability
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DeactivateAbility();
    virtual void DeactivateAbility_Implementation() {}

	// Updates the ability if needed
	UFUNCTION(BlueprintNativeEvent)
	void UpdateAbility(float DeltaTime);
	virtual void UpdateAbility_Implementation(float DeltaTime) {}

protected:
	UPROPERTY(BlueprintReadOnly, Transient, SkipSerialization)
	class AMRCharacter* OwnerCharacter;
};
