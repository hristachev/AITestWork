// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "ATWGAIController.generated.h"

class UATWGAIPerceptionComponent;

UCLASS()
class AITESTWORK_API AATWGAIController : public AAIController
{
	GENERATED_BODY()

public:
	AATWGAIController();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "AI")
	AATWGAICharacter* GetPossesedActor() const { return PossesedActor; }
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UATWGAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	FName FocusOnKeyName = "EnemyActor";
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;

private:
	AATWGAICharacter* PossesedActor;
	
	AActor* GetFocusOnActor() const;
	
};
