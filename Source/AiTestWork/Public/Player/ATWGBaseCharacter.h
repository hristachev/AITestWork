// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ATWGBaseCharacter.generated.h"

class UATWGWeaponComponent;

UCLASS()
class AITESTWORK_API AATWGBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AATWGBaseCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual bool IsRunning() const;
	
	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;

};
