// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/P3D_PauseMenuWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "P3D_GameMode.h"
#include "P3D_PlayerController.h"
#include "HUD/P3D_HUD.h"

void UP3D_PauseMenuWidget::ResumeGame()
{
	auto GameMode = Cast<AP3D_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	auto PC = Cast<AP3D_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	auto HUD = Cast<AP3D_HUD>(PC->GetHUD());
	HUD->AddPlayWidgetToViewport();
	GameMode->ClearPause();

}

void UP3D_PauseMenuWidget::QuitGame()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UKismetSystemLibrary::QuitGame(GetWorld(), PC, EQuitPreference::Quit, true);
}

void UP3D_PauseMenuWidget::OpenOptions()
{

}
