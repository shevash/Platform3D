// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "P3D_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class PLATOFRMER3D_API AP3D_GameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AP3D_GameMode();
private:
	int32 Seconds = 0;

public:
	FTimerHandle ClockTimerHandle;
	virtual void BeginPlay() override;
	int32 GetSeconds() { return Seconds; }
	void incrementSeconds();
	void FinishLevel();
};
