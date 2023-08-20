// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/InteractableActor.h"

#include "BrainComponent.h"
#include "AI/ATWGAIController.h"
#include "Components/BoxComponent.h"

AInteractableActor::AInteractableActor()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	StaticMeshComponent->SetupAttachment(RootComponent);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxCollider->SetupAttachment(StaticMeshComponent);

}


void AInteractableActor::ChangeAIBrainsState()
{
	for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if(!Controller) continue;

		const auto AIController = Cast<AATWGAIController>(Controller);
		if (AIController)
		{
			if(bIsAIOn)
			{
				AIController->BrainComponent->Cleanup();
			}
			else
			{
				AIController->BrainComponent->RestartLogic();
			}
		}
	}

	bIsAIOn = !bIsAIOn;
}

void AInteractableActor::Interact_Implementation(AActor* InteractedActor)
{
	ChangeAIBrainsState();

}




