// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/P3D_UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "P3D_GameMode.h"
#include "P3D_GameInstance.h"

int32 UP3D_UserWidget::GetTime()
{
	AP3D_GameMode* GameMode = Cast<AP3D_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	Seconds = GameMode->GetTime();
	return Seconds;
}

void UP3D_UserWidget::UpdateTime(int32 Sec)
{
	Seconds = Sec;
}

int32 UP3D_UserWidget::GetScore()
{
	UP3D_GameInstance* GameInstance = Cast<UP3D_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	Score=GameInstance->GetScore();
	return Score;
}

void UP3D_UserWidget::UpdateScore(int32 Points)
{
	Score = Points;
}

void UP3D_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UP3D_GameInstance* GameInstance = Cast<UP3D_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->UpdateScore.AddUObject(this, &UP3D_UserWidget::UpdateScore);
	AP3D_GameMode* GameMode = Cast<AP3D_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->OnIncrementSeconds.AddUObject(this, &UP3D_UserWidget::UpdateTime);

}


