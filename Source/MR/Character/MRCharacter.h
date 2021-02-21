// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MRCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class AMRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMRCharacter();

	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE UCameraComponent* GetFirstPersonCameraComponent() const { return CameraComponent; }

	virtual void PreInitializeComponents() override;
protected:
	virtual void BeginPlay();

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

protected:
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MR Components")
	class UMRControlComponent* ControlComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MR Components")
	class UMRAbilityComponent* AbilityComponent;

	UPROPERTY(Transient, SkipSerialization)
	class UMRDetectionComponent* DetectionComponent;
};

