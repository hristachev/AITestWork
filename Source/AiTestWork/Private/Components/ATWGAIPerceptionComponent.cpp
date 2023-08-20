// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ATWGAIPerceptionComponent.h"
#include "AI/ATWGAIController.h"
#include "AiTestWork/Public/Utils.h"
#include "Components/ATWGHealthComponent.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Hearing.h"

#include "Perception/AISense_Sight.h"

AActor* UATWGAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	GetCurrentlyPerceivedActors(UAISense_Hearing::StaticClass(), PercieveActors);
	GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), PercieveActors);
	
	if(PercieveActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if(!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for (const auto PercieveActor : PercieveActors)
	{
		const auto PercievePawn = Cast<APawn>(PercieveActor);
		const auto AreEnemies = PercievePawn && ATWGUtils::AreEnemies(Controller, PercievePawn->Controller);
		if (AreEnemies)
		{
			const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PercieveActor;
			}
		}
	}

	return BestPawn;
}

