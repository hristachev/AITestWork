// Copyright Epic Games, Inc. All Rights Reserved.


#include "AiTestWorkGameModeBase.h"
#include "Player/ATWGPlayerState.h"
#include "Public/Player/ATWGPlayer.h"
#include "Public/Player/ATWGPlayerController.h"
#include "UI/ATWGGameHUD.h"
#include "AIController.h"

AAiTestWorkGameModeBase::AAiTestWorkGameModeBase()
{
	DefaultPawnClass = AATWGPlayer::StaticClass();
	PlayerControllerClass = AATWGPlayerController::StaticClass();
	HUDClass = AATWGGameHUD::StaticClass();
	PlayerStateClass = AATWGPlayerState::StaticClass();
}

void AAiTestWorkGameModeBase::StartPlay()
{
	Super::StartPlay();

	CreateTeamsInfo();
}

UClass* AAiTestWorkGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AAiTestWorkGameModeBase::CreateTeamsInfo()
{
	if (!GetWorld()) return;

	int32 TeamID = 0;
	for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if(!Controller) continue;

		const auto PlayerState = Cast<AATWGPlayerState>(Controller->PlayerState);
		if(!PlayerState) continue;

		if(Controller->GetClass() == PlayerControllerClass)
		{
			TeamID = 0;
			PlayerState->SetTeamID(TeamID);
		}
		else
		{
			TeamID = 1;
			PlayerState->SetTeamID(TeamID);
		}

		UE_LOG(LogTemp, Warning, TEXT("Actor: %s | %i team id"), *Controller->GetPawn()->GetName(), TeamID);
	}
}
