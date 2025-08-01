// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "P3D_HUD.generated.h"

/**
 * 
 */
UCLASS()
class PLATOFRMER3D_API AP3D_HUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameHUDWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> FinishLevelHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PauseHUDWidgetClass;
	UUserWidget* PlayerHUDWidget;

public:
	virtual void BeginPlay() override;
	void AddPlayWidgetToViewport();
	void AddFinishLevelWidgetToViewport();
	void AddPauseWidgetToViewport();


};
