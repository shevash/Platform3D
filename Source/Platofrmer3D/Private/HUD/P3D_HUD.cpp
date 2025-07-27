// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/P3D_HUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "P3D_GameMode.h"
#include "HUD/P3D_FinishLevelWidget.h"

void AP3D_HUD::BeginPlay()
{
	Super::BeginPlay();
	AddPlayWidgetToViewport();
	
}

void AP3D_HUD::AddPlayWidgetToViewport()
{
	auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), GameHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
	}
}

void AP3D_HUD::AddFinishLevelWidgetToViewport()
{
	auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), FinishLevelHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
	}
}

void AP3D_HUD::DrawHUD()
{
	Super::DrawHUD();

}