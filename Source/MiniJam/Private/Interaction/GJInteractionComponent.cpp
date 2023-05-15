// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/GJInteractionComponent.h"
#include "Interaction/GJInteractionInterface.h"

// Sets default values for this component's properties
UGJInteractionComponent::UGJInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	TraceRadius = 15.0f;
	TraceDistance = 300.0f;
	CollisionChannel = ECC_WorldDynamic;
	bDisplayDebugTraces = false;
}

// Called when the game starts
void UGJInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGJInteractionComponent::Interact()
{
	if (FocusedActor != nullptr)
	{
		APawn* MyPawn = Cast<APawn>(GetOwner());
		IGJInteractionInterface::Execute_Interact(FocusedActor, MyPawn);
	}
}

void UGJInteractionComponent::FindBestInteractable()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);

	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * TraceDistance);

	TArray<FHitResult> Hits;
	FCollisionShape Shape;
	Shape.SetSphere(TraceRadius);

	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams,
	                                                       Shape);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
	if (bDisplayDebugTraces)
	{
		DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 0.5f, 0, 0.0f);
	}

	if (bBlockingHit)
	{
		for (FHitResult Hit : Hits)
		{
			if (bDisplayDebugTraces)
			{
				DrawDebugSphere(GetWorld(), Hit.ImpactPoint, TraceRadius, 32, LineColor, false, 0.0f);
			}

			AActor* HitActor = Hit.GetActor();
			if (HitActor && HitActor->Implements<UGJInteractionInterface>())
			{
				auto MeshComp = HitActor->FindComponentByClass<UMeshComponent>();

				//Change the overlay material when the current focussedactor is not equal to the hit actor to save some cpu cycles.				
				if (HitActor != FocusedActor && MeshComp != nullptr && HighlightMaterial != nullptr)
				{
					MeshComp->SetOverlayMaterial(HighlightMaterial);
				}
				FocusedActor = HitActor;
				break;
			}

			if (bDisplayDebugTraces)
			{
				DrawDebugSphere(GetWorld(), Hit.ImpactPoint, TraceRadius, 32, LineColor, false, 0.0f);
			}
		}
		return;
	}

	if (FocusedActor != nullptr)
	{
		auto MeshComp = FocusedActor->FindComponentByClass<UMeshComponent>();
		if (MeshComp != nullptr && HighlightMaterial != nullptr)
		{
			MeshComp->SetOverlayMaterial(nullptr);
		}
	}

	FocusedActor = nullptr;
}

// Called every frame
void UGJInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FindBestInteractable();
}
