// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "P3D_MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLATOFRMER3D_API UP3D_MainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	UFUNCTION(BlueprintCallable)
	void ChooseLevel();
	UFUNCTION(BlueprintCallable)
	void NewGame();
	UFUNCTION(BlueprintCallable)
	void Quit();
	
};
