// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AiTestWorkGameModeBase.generated.h"

class AAIController;

UCLASS()
class AITESTWORK_API AAiTestWorkGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAiTestWorkGameModeBase();

	virtual void StartPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;

private:
	void CreateTeamsInfo();

};
