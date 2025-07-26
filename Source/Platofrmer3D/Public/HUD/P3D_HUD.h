// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
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

public:
	virtual void BeginPlay() override;



};
