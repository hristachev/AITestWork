// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/ATWGBaseCharacter.h"
#include "ATWGAICharacter.generated.h"

class UATWGHealthComponent;
class UBehaviorTree;

UCLASS()
class AITESTWORK_API AATWGAICharacter : public AATWGBaseCharacter
{
	GENERATED_BODY()

public:
	AATWGAICharacter();

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathAnimMontage;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UATWGHealthComponent* HealthComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float LifeSpanOnDeath = 5.0f;

	void SetMaxSpeed(float Value);

protected:
	virtual void BeginPlay() override;
	
	void OnDeath();

	void OnHealthChanged(float Health, float HealthDelta);

	virtual bool IsRunning() const override;


};
