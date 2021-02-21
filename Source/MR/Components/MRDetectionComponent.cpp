// Fill out your copyright notice in the Description page of Project Settings.


#include "MRDetectionComponent.h"
#include "MRDetectableComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UMRDetectionComponent::UMRDetectionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	AngleOfDetection = 45.f;
	TimeBetweenDetections = 0.2f;
	// ...
}


void UMRDetectionComponent::AddDetectedComponent(UMRDetectableComponent* ComponentToAdd)
{
	DetectableComponents.AddUnique(ComponentToAdd);
	// if the detection is enabled and not active, start it
	if (bIsDetectionEnabled && !GetWorld()->GetTimerManager().IsTimerActive(DetectionHandle))
	{
		StartDetection();
	}
}

void UMRDetectionComponent::RemoveDetectedComponent(UMRDetectableComponent* ComponentToRemove)
{
	DetectableComponents.Remove(ComponentToRemove);
	// if there are no elements left
	if (DetectableComponents.Num() == 0)
	{
		StopDetection();
	}
}

void UMRDetectionComponent::EnableDetection()
{
	// Enable the detection, if there are any detectable objects, enable it
	bIsDetectionEnabled = true;
	if (DetectableComponents.Num() > 0)
	{
		StartDetection();
	}
}

void UMRDetectionComponent::DisableDetection()
{
	bIsDetectionEnabled = false;
	StopDetection();
}

bool UMRDetectionComponent::Interact()
{
	bool bHasInteracted = false;
	if (ClosestDetectableComponent)
	{
		bHasInteracted = ClosestDetectableComponent->Interact(GetOwner());
	}
	return bHasInteracted;
}

void UMRDetectionComponent::BeginPlay()
{
	Super::BeginPlay();
	EnableDetection();
}

void UMRDetectionComponent::StartDetection()
{
	GetWorld()->GetTimerManager().SetTimer(DetectionHandle, this, &ThisClass::UpdateDetection, TimeBetweenDetections, true);
}

void UMRDetectionComponent::StopDetection()
{
	SetClosestDetectableComponent(nullptr);
	GetWorld()->GetTimerManager().ClearTimer(DetectionHandle);
}

void UMRDetectionComponent::UpdateDetection()
{
	// Get the forward vector and start of the owner to know where is he looking
	UCameraComponent* PointOfView = GetOwner()->FindComponentByClass<UCameraComponent>();
	check(PointOfView);
	FVector ForwardVector = PointOfView->GetForwardVector();
	FVector StartVector = PointOfView->GetComponentLocation();

	ForwardVector.Normalize();

	//Initialize variables
	float ClosestAngle = TNumericLimits<float>::Max();
	float ClosestDistanceSquared = TNumericLimits<float>::Max();
	UMRDetectableComponent* NewClosestDetectableObject = nullptr;

	// Search through all the detected objects
	for (auto DetectableComponent : DetectableComponents)
	{
		AActor* DetectableActor = DetectableComponent->GetOwner();
		if (DetectableComponent->IsInteractable())
		{
			FVector DirectionToObject = DetectableActor->GetActorLocation() - StartVector;
			FVector DirectionToObjectNormalized = DirectionToObject.GetSafeNormal();
			//Get the angle to the object
			float CurrentAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(ForwardVector, DirectionToObjectNormalized)));
			
			// It is in range of detection
			if (FMath::Abs(CurrentAngle) < AngleOfDetection)
			{
				if (CurrentAngle < ClosestAngle)
				{
					ClosestAngle = CurrentAngle;
					ClosestDistanceSquared = DirectionToObject.SizeSquared();
					NewClosestDetectableObject = DetectableComponent;
				}
			}
		}
	}

	// Todo Enable visual feedback
	if (ClosestDetectableComponent != NewClosestDetectableObject)
	{
		SetClosestDetectableComponent(NewClosestDetectableObject);
	}
}

void UMRDetectionComponent::SetClosestDetectableComponent(UMRDetectableComponent* NewClosestDetectableObject)
{
	ClosestDetectableComponent = NewClosestDetectableObject;
	OnDetectedActorChanged.Broadcast(ClosestDetectableComponent ? ClosestDetectableComponent->GetOwner() : nullptr);
}

