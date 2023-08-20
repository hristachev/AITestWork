// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInteractionFinished, AActor* /*Interactable*/, AActor* /*Interacted*/);

class AITESTWORK_API IInteractInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact(AActor* InteractedActor);
	UFUNCTION()
	virtual void Interact_Implementation(AActor* InteractedActor) {}

	virtual void InteractionFinished(AActor* InteractableObject, AActor* InteractedActor)
	{
		if (OnInteractionFinished.IsBound())
		{
			OnInteractionFinished.Broadcast(InteractableObject, InteractedActor);
		}
	}

	FOnInteractionFinished OnInteractionFinished;
};
