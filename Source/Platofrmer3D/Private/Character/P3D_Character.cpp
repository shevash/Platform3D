// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/P3D_Character.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "P3D_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "P3D_GameMode.h"
#include "P3D_PlayerController.h"
#include "HUD/P3D_HUD.h"


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
	auto PlayerMovement = GetCharacterMovement();
	PlayerMovement->JumpZVelocity = 1500;
	PlayerMovement->GravityScale = 4.0f;
	//PlayerMovement->MaxWalkSpeed = 1200;
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
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AP3D_Character::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AP3D_Character::StopRun);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AP3D_Character::PauseMenu);

}

void AP3D_Character::WalkForward(float Amount)
{
	if (isRun)
	{
		GetCharacterMovement()->MaxWalkSpeed = RunVelocity;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = Velocity;
	}
	AddMovementInput(GetActorForwardVector(), Amount);

}


void AP3D_Character::WalkRight(float Amount)
{
	if (isRun)
	{
		GetCharacterMovement()->MaxWalkSpeed = RunVelocity;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = Velocity;
	}
	AddMovementInput(GetActorRightVector(), Amount);

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

void AP3D_Character::Run()
{
	isRun = true;
	UE_LOG(LogCharacter, Log, TEXT("Run"))
}

void AP3D_Character::StopRun()
{
	isRun = false;
}

void AP3D_Character::PauseMenu()
{
	
	auto GameMode = Cast<AP3D_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	auto PC = Cast<AP3D_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	auto HUD = Cast<AP3D_HUD>(PC->GetHUD());
	if (GameMode->IsPaused())
	{
		GameMode->ClearPause();
		HUD->AddPlayWidgetToViewport();
	}
	else
	{
		GameMode->SetPause(PC);
		HUD->AddPauseWidgetToViewport();
	}

}



void AP3D_Character::AddPointsToScore(int32 Points)
{
	auto GameInstance = Cast<UP3D_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->AddScore(Points);
	UE_LOG(LogCharacter,Log,TEXT("%d"),GameInstance->GetScore())
}
