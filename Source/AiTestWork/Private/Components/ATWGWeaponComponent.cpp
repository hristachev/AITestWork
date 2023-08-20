// Fill out your copyright notice in the Description page of Project Settings.


#include "AiTestWork/Public/Components/ATWGWeaponComponent.h"

#include "AiTestWork/Public/Weapon/ATWGWeapon.h"
#include "GameFramework/Character.h"

UATWGWeaponComponent::UATWGWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UATWGWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

bool UATWGWeaponComponent::CanFire() const
{
	return CurrentWeapon != nullptr;
}

void UATWGWeaponComponent::SpawnWeapon()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld()) return;
	
	auto Weapon = GetWorld()->SpawnActor<AATWGWeapon>(WeaponData.WeaponClass);
	if (!Weapon) return;

	CurrentWeapon = Weapon;
	Weapon->SetOwner(Character);
	AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponEquipSocketName);
}

void UATWGWeaponComponent::AttachWeaponToSocket(AATWGWeapon* Weapon, USceneComponent* SceneComponent,
	const FName& SocketName)
{
	if(!Weapon || !SceneComponent) return;
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UATWGWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character) return;

	Character->PlayAnimMontage(Animation);
}

void UATWGWeaponComponent::StartFire()
{
	if (!CanFire()) return;
	PlayAnimMontage(WeaponData.FireAnimMontage);
	CurrentWeapon->StartFire();
}

void UATWGWeaponComponent::StopFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}



