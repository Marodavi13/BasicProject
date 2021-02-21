// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "MRActivableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActivated, FGameplayTag, Message);

//This component allows to any actor which has it to be activated
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MR_API UMRActivableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMRActivableComponent();

	//Called when activated, it has message support in order to do different things based on the message received
	void ActivateComponent(FGameplayTag Message = FGameplayTag());
public:
	// Called when activated
	UPROPERTY(BlueprintAssignable)
	FOnActivated OnActivated;
	
protected:
	// True if this component can be activated
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanBeActivated;
};
