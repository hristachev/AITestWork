// Fill out your copyright notice in the Description page of Project Settings.

#include "AiTestWork/Public/Player/ATWGBaseCharacter.h"
#include "Components/ATWGWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AATWGBaseCharacter::AATWGBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AATWGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GetCharacterMovement());
}

void AATWGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AATWGBaseCharacter::IsRunning() const
{
	return false;
}


float AATWGBaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;
	
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

