// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/GJGameplayFunctionLibrary.h"

#include "Common/GJHealthComponent.h"

bool UGJGameplayFunctionLibrary::DamageActor(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	if (UGJHealthComponent* HealthComponent = UGJHealthComponent::GetHealthComponent(TargetActor))
	{
		HealthComponent->ApplyHealthChange(DamageCauser, -DamageAmount);
		return true;
	}
	return false;
}

bool UGJGameplayFunctionLibrary::HealActor(AActor* HealerActor, AActor* TargetActor, float HealAmount)
{
	if (UGJHealthComponent* HealthComponent = UGJHealthComponent::GetHealthComponent(TargetActor))
	{
		HealthComponent->ApplyHealthChange(HealerActor, HealAmount);
		return true;
	}
	return false;
}
