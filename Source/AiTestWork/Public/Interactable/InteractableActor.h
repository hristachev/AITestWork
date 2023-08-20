// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractInterface.h"
#include "InteractableActor.generated.h"

class UBoxComponent;

UCLASS()
class AITESTWORK_API AInteractableActor : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	AInteractableActor();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxCollider;
	
	UFUNCTION()
	void ChangeAIBrainsState();
public:
	virtual void Interact_Implementation(AActor* InteractedActor) override;
private:
	bool bIsAIOn = true;
};
