// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/P3D_HUD.h"
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
	if(PlayerHUDWidget != nullptr)	PlayerHUDWidget->RemoveFromParent();
	PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), GameHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		auto PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PC->bShowMouseCursor = false;
		PlayerHUDWidget->AddToViewport();
		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);
	}
}

void AP3D_HUD::AddFinishLevelWidgetToViewport()
{
	if (PlayerHUDWidget != nullptr)	PlayerHUDWidget->RemoveFromParent();
	PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), FinishLevelHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		auto PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerHUDWidget->AddToViewport();
		PC->bShowMouseCursor = true;
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(PlayerHUDWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PC->SetInputMode(InputMode);
	}
}

void AP3D_HUD::AddPauseWidgetToViewport()
{
	if (PlayerHUDWidget != nullptr)	PlayerHUDWidget->RemoveFromParent();
	PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PauseHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		auto PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PC->bShowMouseCursor = true;
		PlayerHUDWidget->AddToViewport();
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(PlayerHUDWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PC->SetInputMode(InputMode);
	}
}

void AP3D_HUD::DrawHUD()
{
	Super::DrawHUD();

}