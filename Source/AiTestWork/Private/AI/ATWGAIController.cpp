// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/ATWGAIController.h"
#include "AI/ATWGAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/ATWGAIPerceptionComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"

AATWGAIController::AATWGAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UATWGAIPerceptionComponent>("AIPerceptionComponent");
	SetPerceptionComponent(*AIPerceptionComponent);

	bWantsPlayerState = true;
}

void AATWGAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AATWGAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossesedActor = Cast<AATWGAICharacter>(InPawn);
	if (PossesedActor)
	{
		RunBehaviorTree(PossesedActor->BehaviorTree);
	}
}

void AATWGAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}

AActor* AATWGAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
