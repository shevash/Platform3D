// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/P3D_FinishLevelWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "P3D_GameInstance.h"

void UP3D_FinishLevelWidget::QuitGame()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UKismetSystemLibrary::QuitGame(GetWorld(), PC, EQuitPreference::Quit, true);
}

void UP3D_FinishLevelWidget::NextLevel()
{
	auto GameInstance = Cast<UP3D_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance->GetCurrentLevel() < GameInstance->GetLevelsNum()-1)
	{
		GameInstance->SetCurrentLevel((GameInstance->GetCurrentLevel())+1);
	}
		UGameplayStatics::OpenLevel(this, GameInstance->GetLevelName(GameInstance->GetCurrentLevel()), true);
}
