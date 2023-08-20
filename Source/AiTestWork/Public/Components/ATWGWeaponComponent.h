// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ATWGWeaponComponent.generated.h"

class AATWGWeapon;

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AATWGWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UAnimMontage* FireAnimMontage;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AITESTWORK_API UATWGWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UATWGWeaponComponent();

	void StartFire();
	void StopFire();

	
protected:
	virtual void BeginPlay() override;

	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FWeaponData WeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY()
	AATWGWeapon* CurrentWeapon = nullptr;
	
	bool CanFire() const;
	
private:
	void SpawnWeapon();

	void AttachWeaponToSocket(AATWGWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	void PlayAnimMontage(UAnimMontage* Animation);
	
};
