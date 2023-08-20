// Fill out your copyright notice in the Description page of Project Settings.


#include "AiTestWork/Public/Player/ATWGPlayer.h"

#include "AiTestWork/Public/Components/ATWGWeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AATWGPlayer::AATWGPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponComponent = CreateDefaultSubobject<UATWGWeaponComponent>("WeaponComponent");

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComponent");
	InteractionComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AATWGPlayer::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponComponent);
	check(InteractionComponent);
}

void AATWGPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	check(WeaponComponent);
	

	PlayerInputComponent->BindAxis("MoveForward", this, &AATWGPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AATWGPlayer::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AATWGPlayer::LookUp);
	PlayerInputComponent->BindAxis("TurnAround", this, &AATWGPlayer::TurnAround);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AATWGPlayer::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AATWGPlayer::OnStopRunning);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UATWGWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UATWGWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, InteractionComponent, &UInteractionComponent::Interact);
}

bool AATWGPlayer::IsRunning() const
{
	return WantsToRun && !GetVelocity().IsZero();
}

void AATWGPlayer::MoveForward(float Amount)
{
	if (Amount == 0.0f) return;

	if (WantsToRun == true)
	{
		MakeNoise(0.5f, this, GetActorLocation());
	}
	
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AATWGPlayer::MoveRight(float Amount)
{
	if (Amount == 0.0f) return;

	if (WantsToRun == true)
	{
		MakeNoise(0.5f, this, GetActorLocation());
	}
	
	AddMovementInput(GetActorRightVector(), Amount);
}

void AATWGPlayer::LookUp(float Amount)
{
	AddControllerPitchInput(Amount);
}

void AATWGPlayer::TurnAround(float Amount)
{
	AddControllerYawInput(Amount);

}

void AATWGPlayer::OnStartRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 360.0f;
	WantsToRun = true;
}

void AATWGPlayer::OnStopRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 120.0f;
	WantsToRun = false;
}
