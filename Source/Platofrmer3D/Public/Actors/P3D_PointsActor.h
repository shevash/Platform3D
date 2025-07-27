// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "P3D_PointsActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class USceneComponent;
UCLASS()
class PLATOFRMER3D_API AP3D_PointsActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AP3D_PointsActor();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBoxComponent* BoxCollision;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* SceneComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	FTimerHandle RotateTimer;
	void RotateMesh();
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Score")
	int32 Points = 10;

	UFUNCTION()
	void OnCharBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
}
;