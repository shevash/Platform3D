// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUD/P3D_UserWidget.h"
#include "P3D_FinishLevelWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLATOFRMER3D_API UP3D_FinishLevelWidget : public UP3D_UserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void QuitGame();
	UFUNCTION(BlueprintCallable)
	void NextLevel();
};
