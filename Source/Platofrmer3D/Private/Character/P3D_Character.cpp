// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/P3D_Character.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"


DEFINE_LOG_CATEGORY_STATIC(LogCharacter,All,All)
// Sets default values
AP3D_Character::AP3D_Character()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->TargetArmLength = 600.0f;
	//SpringArm->bUsePawnControlRotation = true;
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 100.0f);
	SpringArm->AttachTo(GetRootComponent());
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->AttachTo(SpringArm);

	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AP3D_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AP3D_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AP3D_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward",this,&AP3D_Character::WalkForward);
	PlayerInputComponent->BindAxis("MoveRight",this, &AP3D_Character::WalkRight);
	PlayerInputComponent->BindAxis("Pitch", this, &AP3D_Character::TurnUp);
	PlayerInputComponent->BindAxis("Yaw", this, &AP3D_Character::TurnRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed,this,&ACharacter::Jump);

}

void AP3D_Character::WalkForward(float Amount)
{
	auto Speed = Velocity * Amount;
	UE_LOG(LogCharacter, Log, TEXT("%f"), Speed);
	AddMovementInput(GetActorForwardVector(), Speed);
}


void AP3D_Character::WalkRight(float Amount)
{
	auto Speed = Velocity * Amount;
	AddMovementInput(GetActorRightVector(), Speed);
}

void AP3D_Character::TurnRight(float Amount)
{
	AddControllerYawInput(Amount);
}

void AP3D_Character::TurnUp(float Amount)
{
	FRotator CurrentRotation = SpringArm->GetRelativeRotation();
	float NewPitch = FMath::Clamp(CurrentRotation.Pitch + Amount, -80.0f, 80.0f);
	SpringArm->SetRelativeRotation(FRotator(NewPitch, CurrentRotation.Yaw, CurrentRotation.Roll));
}
