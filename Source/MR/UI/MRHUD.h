// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "MRHUD.generated.h"

UCLASS()
class MR_API AMRHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMRHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;
protected:
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> HUDClass;
	
	UPROPERTY(Transient,SkipSerialization, BlueprintReadWrite)
	UUserWidget* HUD;
};

