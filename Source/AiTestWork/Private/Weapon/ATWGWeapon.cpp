// Fill out your copyright notice in the Description page of Project Settings.


#include "AiTestWork/Public/Weapon/ATWGWeapon.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Character.h"
#include "Player/ATWGPlayer.h"
#include "Weapon/Components/ATWGWeaponFXComponent.h"

// Sets default values
AATWGWeapon::AATWGWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMeshComponent);

	WeaponFXComponent = CreateDefaultSubobject<UATWGWeaponFXComponent>("WeaponFXComponent");

}

void AATWGWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMeshComponent);
	check(WeaponFXComponent);
}

void AATWGWeapon::StartFire()
{
	const auto Player = Cast<AATWGPlayer>(GetOwner());
	
	InitMuzzleFX();

	if (Player)
	{
		MakeNoise(1.0f, Player, WeaponMeshComponent->GetSocketLocation(MuzzleSocketName));
	}
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AATWGWeapon::MakeShot, TimeBetweenShots, true);
	MakeShot();
}

void AATWGWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
	SetMuzzleFXVisibility(false);
}

void AATWGWeapon::MakeShot()
{
	if (!GetWorld())
	{
		StopFire();
		return;
	}
	
	FVector TraceStart, TraceEnd;
	if(!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}
	
	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);
	
	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		WeaponFXComponent->PlayImpactFX(HitResult);
	}
}

bool AATWGWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation,ViewRotation)) return false;
	
	TraceStart = ViewLocation;
	const FVector ShootDirection = ViewRotation.Vector(); 
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

	return true;
}

bool AATWGWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto ATWGCharacter = Cast<ACharacter>(GetOwner());
	if(!ATWGCharacter) return false;

	if (ATWGCharacter->IsPlayerControlled())
	{
		const auto Controller = ATWGCharacter->GetController<APlayerController>();;
		if(!Controller) return false;
	
		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}
	else
	{
		ViewLocation = GetMuzzleWorldLocation();
		ViewRotation = WeaponMeshComponent->GetSocketRotation(MuzzleSocketName);
	}
	
	return true;
}

FVector AATWGWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMeshComponent->GetSocketLocation(MuzzleSocketName);
}

void AATWGWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if(!GetWorld()) return;
	
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	CollisionQueryParams.bReturnPhysicalMaterial = true;
	
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionQueryParams);
}

UNiagaraComponent* AATWGWeapon::SpawnMuzzleFX()
{
	return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX, WeaponMeshComponent, MuzzleSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);

}

void AATWGWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();
	if(!DamagedActor) return;

	DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetController(), this);
}

void AATWGWeapon::InitMuzzleFX()
{
	if (!MuzzleFXComponent)
	{
		MuzzleFXComponent = SpawnMuzzleFX();
	}
	SetMuzzleFXVisibility(true);
}

void AATWGWeapon::SetMuzzleFXVisibility(bool Visible)
{
	if (MuzzleFXComponent)
	{
		MuzzleFXComponent->SetPaused(!Visible);
		MuzzleFXComponent->SetVisibility(Visible, true);
	}
}

AController* AATWGWeapon::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}

