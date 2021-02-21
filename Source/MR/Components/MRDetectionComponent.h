// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MRDetectionComponent.generated.h"

class UMRDetectableComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDetectedActorChanged, AActor*, DetectedActor);

// This component allows to detect actors with Detectable components and interact with them
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MR_API UMRDetectionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMRDetectionComponent();

	// Adds a new detectable object
	void AddDetectedComponent(UMRDetectableComponent* ComponentToAdd);
	// Removes a detectable component
	void RemoveDetectedComponent(UMRDetectableComponent* ComponentToRemove);

	// Enables the detection and starts it if there is any object in range
	UFUNCTION(BlueprintCallable)
	void EnableDetection();
	// Disables the detection
	UFUNCTION(BlueprintCallable)
	void DisableDetection();

	// Interacts with the closest object
	bool Interact();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Detection handling
	void StartDetection();
	void StopDetection();
	void UpdateDetection();

	// Sets the detectable component and broadcasts the delegate
	void SetClosestDetectableComponent(UMRDetectableComponent* NewClosestDetectableObject);

public:
	UPROPERTY(BlueprintAssignable)
	FOnDetectedActorChanged OnDetectedActorChanged;
protected:

	// Angle from forward vector in which the actors will be detected
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AngleOfDetection;

	// Time between detections as we don't need it in the tick()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TimeBetweenDetections;


	// Array of all the Detectable objects
	UPROPERTY(Transient, SkipSerialization, BlueprintReadOnly)
	TArray<UMRDetectableComponent*> DetectableComponents;

	// Reference to the closest detectable object
	UPROPERTY(Transient, SkipSerialization, BlueprintReadOnly)
	UMRDetectableComponent* ClosestDetectableComponent;

	//True if this component is detecting
	UPROPERTY(Transient, SkipSerialization, BlueprintReadOnly)
	bool bIsDetectionEnabled;


	FTimerHandle DetectionHandle;
};
