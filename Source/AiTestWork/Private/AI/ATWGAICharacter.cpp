// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ATWGAICharacter.h"
#include "BrainComponent.h"
#include "AI/ATWGAIController.h"
#include "Components/ATWGHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AATWGAICharacter::AATWGAICharacter()
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = AATWGAIController::StaticClass();

	HealthComponent = CreateDefaultSubobject<UATWGHealthComponent>("HealthComponent");

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

void AATWGAICharacter::SetMaxSpeed(float Value)
{
	GetCharacterMovement()->MaxWalkSpeed = Value;
}

void AATWGAICharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnDeath.AddUObject(this, &AATWGAICharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &AATWGAICharacter::OnHealthChanged);
}

void AATWGAICharacter::OnDeath()
{
	PlayAnimMontage(DeathAnimMontage);
	
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(LifeSpanOnDeath);
	
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	
	
	const auto ATWGController = Cast<AAIController>(Controller);
	if (ATWGController && ATWGController->BrainComponent)
	{
		ATWGController->BrainComponent->Cleanup();
	}
}

void AATWGAICharacter::OnHealthChanged(float Health, float HealthDelta)
{
}

bool AATWGAICharacter::IsRunning() const
{
	return GetCharacterMovement()->MaxWalkSpeed >= 140.0f;
}
