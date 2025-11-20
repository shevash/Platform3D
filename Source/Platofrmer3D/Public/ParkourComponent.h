// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ParkourComponent.generated.h"


class USphereComponent;
class UBoxComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATOFRMER3D_API UParkourComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UParkourComponent();

	UPROPERTY(VisibleAnywhere)
	USphereComponent* WallJumpSphereComponent;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* WallClimbPermitBoxComponent;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* WallClimbDeniedBoxComponent;
	UPROPERTY(EditDefaultsOnly)
	int32 DoubleJumpCount = 1;
	UPROPERTY(EditDefaultsOnly)
	int32 JumpMaxCount = 99999;

	int32 JumpCount = 0;
	bool bDoubleJumpPossible = false;
	bool bNearWall = false;
	bool bPermitToClimb = false;
	bool bDeniedToClimb = false;
	bool bHoldingOn = false;
	AActor* PermitActor = nullptr;
	AActor* DeniedActor = nullptr;
	FHitResult WallClimbPermitBoxHitResult;
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

	UFUNCTION()
	void OnWallClimbPermitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnWallClimbPermitBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnWallClimbDeniedBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnWallClimbDeniedBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool CanDoubleJump() { return bDoubleJumpPossible; }
	bool CanClimb() {return (bPermitToClimb && bDeniedToClimb) || (!bPermitToClimb && !bDeniedToClimb);}
	void IncrementJumpCount() { JumpCount++; }
	void ResetJump();
	void ClimbUp();
	void HoldOnLedge();
	void HoldingOnCharacterPosition();
};
