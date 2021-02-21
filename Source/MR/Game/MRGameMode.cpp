// Copyright Epic Games, Inc. All Rights Reserved.

#include "MRGameMode.h"
#include "MR/UI/MRHUD.h"
#include "MR/Character/MRCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMRGameMode::AMRGameMode()
	: Super()
{
	// use our custom HUD class
	HUDClass = AMRHUD::StaticClass();
}
