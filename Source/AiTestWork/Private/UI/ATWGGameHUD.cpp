// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ATWGGameHUD.h"
#include "Blueprint/UserWidget.h"

void AATWGGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AATWGGameHUD::BeginPlay()
{
	Super::BeginPlay();

	InitWidget();
}

void AATWGGameHUD::InitWidget()
{
	if(!PlayerHUDWidgetClass || !GetWorld()) return;

	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
	if (CurrentWidget)
	{
		CurrentWidget->AddToViewport();
	}
}
