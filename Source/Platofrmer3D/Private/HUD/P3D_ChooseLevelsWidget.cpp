// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/P3D_ChooseLevelsWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "P3D_GameInstance.h"

void UP3D_ChooseLevelsWidget::StartLevel(int32 index)
{
	auto GameInstance = Cast<UP3D_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UGameplayStatics::OpenLevel(this, GameInstance->GetLevelName(index), true);
}
