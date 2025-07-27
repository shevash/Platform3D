// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "P3D_GameInstance.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FUpdateScore,int32 Score)
UCLASS()
class PLATOFRMER3D_API UP3D_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	FUpdateScore UpdateScore;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Score = 0;

public:
	int32 GetScore() { return Score; }
	void AddScore(int32 Points);
};
