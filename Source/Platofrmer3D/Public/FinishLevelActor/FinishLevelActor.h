// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "FinishLevelActor.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnFinish);
class UBoxComponent;
UCLASS()
class PLATOFRMER3D_API AFinishLevelActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFinishLevelActor();

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollision;
	
	FOnFinish OnFinish;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void test(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);
};
