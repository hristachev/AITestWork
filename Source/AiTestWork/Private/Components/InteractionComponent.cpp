// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionComponent.h"

#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"
#include "Interfaces/InteractInterface.h"


UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UInteractionComponent::OnInteractionCompBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UInteractionComponent::OnInteractionCompEndOverlap);
}

void UInteractionComponent::OnInteractionCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UInteractInterface>())
	{
		InteractableActor = OtherActor;

		if (!InteractMessage)
		{
			if (InteractMessageClass)
			{
				InteractMessage = CreateWidget<UUserWidget>(GetWorld(), InteractMessageClass);
			}
		}
		if (InteractMessage && !InteractMessage->IsInViewport())
		{
			InteractMessage->AddToViewport();
		}
	}
}

void UInteractionComponent::OnInteractionCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InteractableActor = nullptr;

	if (InteractMessage)
	{
		InteractMessage->RemoveFromParent();
	}
}

void UInteractionComponent::Interact()
{
	if (InteractableActor)
	{
		IInteractInterface::Execute_Interact(InteractableActor, GetOwner());
	}
}


