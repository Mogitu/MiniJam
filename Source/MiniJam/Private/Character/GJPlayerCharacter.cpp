// Fill out your copyright notice in the Description page of Project Settings.

#include "Character\GJPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Interaction/GJInteractionComponent.h"
#include "Widget/GJUserWidget.h"

// Sets default values
AGJPlayerCharacter::AGJPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->bUsePawnControlRotation = true;

	InteractionComponent = CreateDefaultSubobject<UGJInteractionComponent>(TEXT("Interaction Component"));
}

// Called when the game starts or when spawned
void AGJPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (HudWidgetClass != nullptr)
	{
		HudWidgetInstance = CreateWidget<UGJUserWidget>(GetWorld(), HudWidgetClass);
		HudWidgetInstance->AddToViewport();
	}
}

FVector AGJPlayerCharacter::GetPawnViewLocation() const
{
	return CameraComponent->GetComponentLocation();
}

// Called every frame
void AGJPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGJPlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AGJPlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AGJPlayerCharacter::Turn(float Value)
{
	if (Value != 0.0f)
	{
		AddControllerYawInput(Value);
	}
}

void AGJPlayerCharacter::LookUp(float Value)
{
	if (Value != 0.0f)
	{
		AddControllerPitchInput(Value);
	}
}

void AGJPlayerCharacter::Interact()
{
	InteractionComponent->Interact();
}

// Called to bind functionality to input
void AGJPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGJPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGJPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AGJPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AGJPlayerCharacter::LookUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AGJPlayerCharacter::Interact);
}
