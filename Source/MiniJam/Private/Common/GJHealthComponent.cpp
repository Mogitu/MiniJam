// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/GJHealthComponent.h"

#include "GameMode/GJGameMode.h"

UGJHealthComponent* UGJHealthComponent::GetHealthComponent(AActor* FromActor)
{
	if (FromActor)
	{
		return FromActor->FindComponentByClass<UGJHealthComponent>();
	}
	return nullptr;
}

// Sets default values for this component's properties
UGJHealthComponent::UGJHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	MaxHealth = 100.0f;
	Health = MaxHealth;
}

void UGJHealthComponent::ApplyHealthChange(AActor* Instigator, float Delta)
{
	float OldHealth = Health;
	float NewHealth = FMath::Clamp(Health + Delta, 0.0f, MaxHealth);

	float ActualDelta = NewHealth - OldHealth;

	Health = NewHealth;
	if (ActualDelta != 0.0f)
	{
		OnHealthChanged.Broadcast(Instigator, this, Health, ActualDelta);
	}

	if (ActualDelta < 0.0f && Health == 0.0f)
	{
		AGJGameMode* GM = GetWorld()->GetAuthGameMode<AGJGameMode>();
		if (GM)
		{
			GM->OnActorKilled(GetOwner(), Instigator);
		}
	}
}
