// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Components/ATWGWeaponFXComponent.h"

#include "NiagaraFunctionLibrary.h"
#include "AI/ATWGAICharacter.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"


UATWGWeaponFXComponent::UATWGWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UATWGWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	auto EnemyActor = Cast<AATWGAICharacter>(Hit.GetActor());
	auto DecalData = DefaultDecalData;

	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalData.Material, DecalData.Size, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(DecalData.LifeTime, DecalData.FadeOutTime);
	}

	if (Hit.GetActor() == EnemyActor)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DecalData.BloodFX, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	}
}
