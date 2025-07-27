// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "P3D_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLATOFRMER3D_API UP3D_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	int32 Seconds = 0;
	int32 Score = 0;
public:
	UFUNCTION(BlueprintCallable)
	int32 GetTime();
	void UpdateTime(int32 Sec);
	UFUNCTION(BlueprintCallable)
	int32 GetScore();
	void UpdateScore(int32 Points);

	virtual void NativeConstruct() override;
};
