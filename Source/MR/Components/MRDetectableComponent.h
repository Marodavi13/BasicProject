// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MRDetectableComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteracted,	AActor*, ActorInteracting);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDetected,	AActor*, ActorDetecting);

// This component allows an actor to be detected and interacted
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MR_API UMRDetectableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMRDetectableComponent();

	// Function called to interact with this components
	bool Interact(AActor* ActorInteracting);

	// Returns true if this component is interactable
	FORCEINLINE bool IsInteractable() const { return bIsInteractable; }

	// Initializes the components setting the sphere reference
	virtual void InitializeComponent() override;

protected:
	// Finds the detectable sphere of the actor
	void FindDetectableSphere();

	// Detection Sphere functions
	UFUNCTION()
	virtual void OnBeginOverlap(class UPrimitiveComponent* HitComp = nullptr, class AActor* OtherActor = nullptr, class UPrimitiveComponent* OtherComp = nullptr, int32 OtherBodyIndex = 0, bool bFromSweep = false, const FHitResult& SweepResult = FHitResult());
	UFUNCTION()
	virtual void OnEndOverlap(class UPrimitiveComponent* OverlappedComp = nullptr, class AActor* OtherActor = nullptr, class UPrimitiveComponent* OtherComp = nullptr, int32 OtherBodyIndex = 0);

	//EVENTS
public:
	UPROPERTY(BlueprintAssignable)
	FOnInteracted     OnInteracted;
	UPROPERTY(BlueprintAssignable)
	FOnDetected       OnDetected;

	//MEMBER VARIABLES
public:
	// True if you are able or will be able interact with this component
	UPROPERTY(EditAnywhere)
	bool bIsInteractable;

	// True if you can interact with this component right now
	UPROPERTY(EditAnywhere)
	bool bCanBeInteracted;

	// The detection sphere
	UPROPERTY(Transient, SkipSerialization)
	class USphereComponent* DetectableSphere;
};
