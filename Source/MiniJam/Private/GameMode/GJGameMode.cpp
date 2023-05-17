// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\GameMode\GJGameMode.h"

void AGJGameMode::OnActorKilled(AActor* Victim, AActor* Killer)
{
	Victim->Destroy();
}
