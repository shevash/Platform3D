// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/P3D_UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "P3D_GameMode.h"

int32 UP3D_UserWidget::GetTime()
{
	return Seconds;
}

void UP3D_UserWidget::UpdateTime(int32 Sec)
{
	Seconds = Sec;
}

void UP3D_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	AP3D_GameMode* GameMode = Cast<AP3D_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->OnIncrementSeconds.AddUObject(this, &UP3D_UserWidget::UpdateTime);
}


