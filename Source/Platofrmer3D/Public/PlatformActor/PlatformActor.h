// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class PLATOFRMER3D_API APlatformActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformActor();

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category = "ScaleChangeControl")
	bool xen_scale = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ScaleChangeControl")
	bool yen_scale = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ScaleChangeControl")
	bool zen_scale = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ScaleChangeControl")
	bool xen_move = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ScaleChangeControl")
	bool yen_move = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ScaleChangeControl")
	bool zen_move = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ScaleChangeControl")
	bool xen_rotate = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ScaleChangeControl")
	bool yen_rotate = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ScaleChangeControl")
	bool zen_rotate = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ScaleChangeControl")
	int32 FrequancyScale = 2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ScaleChangeControl")
	int32 FrequancyRotate = 2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ScaleChangeControl")
	int32 FrequancyMove = 2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ScaleChangeControl", meta = (ClampMin = "0.1", ClampMax = "2"))
	float AmplitudeScale = 2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ScaleChangeControl", meta = (ClampMin = "0.1"))
	float AmplitudeRotate = 180;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ScaleChangeControl", meta = (ClampMin = "0.1"))
	float AmplitudeMove = 200;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FVector InitialLocation;
	FVector InitialScale;
	FRotator InitialRotation;

	void ChangeScale(float t);
	void Move(float t);
	void Rotate(float t);
};
