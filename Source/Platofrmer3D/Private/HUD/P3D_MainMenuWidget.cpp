// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/P3D_MainMenuWidget.h"
#include "HUD/P3D_HUD.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "P3D_GameMode.h"
#include "P3D_PlayerController.h"
#include "P3D_GameInstance.h"

void UP3D_MainMenuWidget::ChooseLevel()
{
	auto PC = Cast<AP3D_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	auto HUD = Cast<AP3D_HUD>(PC->GetHUD());
	HUD->AddChooseLevelWidgetToViewport();
}

void UP3D_MainMenuWidget::NewGame()
{
	auto GameInstance = Cast<UP3D_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->SetCurrentLevel(0);
	UGameplayStatics::OpenLevel(this, GameInstance->GetLevelName(GameInstance->GetCurrentLevel()), true);
}

void UP3D_MainMenuWidget::Quit()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UKismetSystemLibrary::QuitGame(GetWorld(), PC, EQuitPreference::Quit, true);
}
