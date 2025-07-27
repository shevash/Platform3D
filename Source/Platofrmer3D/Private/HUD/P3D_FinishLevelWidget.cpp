// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/P3D_FinishLevelWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UP3D_FinishLevelWidget::QuitGame()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UKismetSystemLibrary::QuitGame(GetWorld(), PC, EQuitPreference::Quit, true);
}

void UP3D_FinishLevelWidget::NextLevel()
{
	UGameplayStatics::OpenLevel(this, FName("Level_2"), true);
}
