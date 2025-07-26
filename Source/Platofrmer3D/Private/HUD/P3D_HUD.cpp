// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/P3D_HUD.h"
#include "Blueprint/UserWidget.h"


void AP3D_HUD::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), GameHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
	}
}

void AP3D_HUD::DrawHUD()
{
	Super::DrawHUD();

}