// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ATWGBaseCharacter.h"
#include "ATWGPlayer.generated.h"


class UInteractionComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class AITESTWORK_API AATWGPlayer : public AATWGBaseCharacter
{
	GENERATED_BODY()

public:
	AATWGPlayer();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UATWGWeaponComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UInteractionComponent* InteractionComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	virtual void BeginPlay() override;
	

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual bool IsRunning() const override;

private:
	bool WantsToRun = false;

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void LookUp(float Amount);
	void TurnAround(float Amount);

	void OnStartRunning();
	void OnStopRunning();
};
