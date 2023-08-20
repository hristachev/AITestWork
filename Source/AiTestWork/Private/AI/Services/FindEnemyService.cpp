// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/FindEnemyService.h"
#include "AIController.h"
#include "AiTestWork/Public/Utils.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/ATWGAIPerceptionComponent.h"

UFindEnemyService::UFindEnemyService()
{
	NodeName = "Find Enemy";
}

void UFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = ATWGUtils::GetSTUPlayerComponent<UATWGAIPerceptionComponent>(Controller);
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
