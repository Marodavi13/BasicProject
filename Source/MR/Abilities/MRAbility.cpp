// Fill out your copyright notice in the Description page of Project Settings.


#include "MRAbility.h"

void UMRAbility::InitializeAbility_Implementation(AMRCharacter* Owner)
{
	OwnerCharacter = Owner; 
	check(AbilityTag.IsValid());
}

bool UMRAbility::CanPerformAbility_Implementation() const
{
	return true;
}
