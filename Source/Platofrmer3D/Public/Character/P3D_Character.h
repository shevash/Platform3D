// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "P3D_Character.generated.h"

class USpringArmController;
class UCameraComponent;
UCLASS()
class PLATOFRMER3D_API AP3D_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AP3D_Character();


	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* Camera;
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
	int32 Velocity = 600;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void WalkForward(float Amount);
	void WalkRight(float Amount);
	void TurnRight(float Amount);
	void TurnUp(float Amount);
};
