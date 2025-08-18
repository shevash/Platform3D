// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "P3D_ChooseLevelsWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLATOFRMER3D_API UP3D_ChooseLevelsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void StartLevel(int32 index);
};
