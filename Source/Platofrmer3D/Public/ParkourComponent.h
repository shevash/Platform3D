// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ParkourComponent.generated.h"


class USphereComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATOFRMER3D_API UParkourComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UParkourComponent();

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* WallJumpSphereComponent;
	UPROPERTY(EditDefaultsOnly)
	int32 DoubleJumpCount = 1;
	UPROPERTY(EditDefaultsOnly)
	int32 JumpMaxCount = 99999;

	int32 JumpCount = 0;
	bool bDoubleJumpPossible = false;

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void WallJump();

	UFUNCTION()
	void OnWallJumpSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnWallJumpSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	bool CanDoubleJump() { return bDoubleJumpPossible; }
	void IncrementJumpCount() { JumpCount++; }
	void ResetJump();
};
