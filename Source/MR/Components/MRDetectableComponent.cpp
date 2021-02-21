// Fill out your copyright notice in the Description page of Project Settings.


#include "MRDetectableComponent.h"
#include "Components/SphereComponent.h"
#include "MRDetectionComponent.h"

const FName DetectionSphereTag = TEXT("Detection");

// Sets default values for this component's properties
UMRDetectableComponent::UMRDetectableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
	// ...
}


bool UMRDetectableComponent::Interact(AActor* ActorInteracting)
{
	if (bCanBeInteracted)
	{
		OnInteracted.Broadcast(ActorInteracting);
	}
	return bCanBeInteracted;
}

void UMRDetectableComponent::InitializeComponent()
{ 
	Super::InitializeComponent();
	// Make sure we have a detectable sphere before starting the game
	FindDetectableSphere();
	checkf(DetectableSphere, TEXT("DetectableSphere not found in actor %s"), *GetOwner()->GetName());
	if (DetectableSphere)
	{
		DetectableSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &UMRDetectableComponent::OnBeginOverlap);
		DetectableSphere->OnComponentEndOverlap.AddUniqueDynamic(this,	 &UMRDetectableComponent::OnEndOverlap);
	}
}

void UMRDetectableComponent::FindDetectableSphere()
{
	TArray<USphereComponent*> OwnerSphereComponents;
	GetOwner()->GetComponents(OwnerSphereComponents);
	// Search the detection sphere with the wanted tag
	for (auto* SphereComponent : OwnerSphereComponents)
	{
		if (SphereComponent->ComponentTags.Contains(DetectionSphereTag))
		{
			DetectableSphere = SphereComponent;
			break;
		}
	}
	check(DetectableSphere);
}

void UMRDetectableComponent::OnBeginOverlap(UPrimitiveComponent* HitComp /*= nullptr*/, AActor* OtherActor /*= nullptr*/, UPrimitiveComponent* OtherComp /*= nullptr*/,
											int32 OtherBodyIndex /*= 0*/, bool bFromSweep /*= false*/, const FHitResult& SweepResult /*= FHitResult()*/)
{
	if (IsValid(OtherActor))
	{
		auto DetectionComponent = OtherActor->FindComponentByClass<UMRDetectionComponent>();
		if (DetectionComponent)
		{
			DetectionComponent->AddDetectedComponent(this);
			OnDetected.Broadcast(OtherActor);
		}
	}
}

void UMRDetectableComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComp /*= nullptr*/, AActor* OtherActor /*= nullptr*/, 
										  UPrimitiveComponent* OtherComp /*= nullptr*/,	int32 OtherBodyIndex /*= 0*/)
{
	if (IsValid(OtherActor))
	{
		auto DetectionComponent = OtherActor->FindComponentByClass<UMRDetectionComponent>();
		if (DetectionComponent)
		{
			DetectionComponent->RemoveDetectedComponent(this);
		}
	}
}

