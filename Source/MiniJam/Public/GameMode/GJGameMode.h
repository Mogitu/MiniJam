// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GJGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MINIJAM_API AGJGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	void OnActorKilled(AActor* Victim, AActor* Killer);
};
