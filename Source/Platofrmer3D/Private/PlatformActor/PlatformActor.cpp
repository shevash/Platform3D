// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformActor/PlatformActor.h"

// Sets default values
APlatformActor::APlatformActor()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->AttachTo(GetRootComponent());
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlatformActor::BeginPlay()
{
	Super::BeginPlay();
	InitialScale = GetActorScale3D();
	InitialLocation = GetActorLocation();
	InitialRotation = GetActorRotation();
}

// Called every frame
void APlatformActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float time = GetWorld()->GetTimeSeconds();
	ChangeScale(time);
	Move(time);
	Rotate(time);

}

void APlatformActor::ChangeScale(float t)
{	
	auto CurrentScale = GetActorScale3D();
	CurrentScale.X = InitialScale.X + AmplitudeScale * FMath::Sin(0.1+FrequancyScale * t);
	CurrentScale.Y = InitialScale.Y + AmplitudeScale * FMath::Sin(0.1+FrequancyScale * t);
	CurrentScale.Z = InitialScale.Z + AmplitudeScale * FMath::Sin(0.1+FrequancyScale * t);
	SetActorScale3D(CurrentScale);


}

void APlatformActor::Move(float t)
{
	auto CurrentLocation = GetActorLocation();
	CurrentLocation.X = InitialLocation.X + AmplitudeMove * FMath::Sin(0.1 + FrequancyMove * t);
	CurrentLocation.Y = InitialLocation.Y + AmplitudeMove * FMath::Sin(0.1 + FrequancyMove * t);
	CurrentLocation.Z = InitialLocation.Z + AmplitudeMove * FMath::Sin(0.1 + FrequancyMove * t);
	SetActorLocation(CurrentLocation);
}

void APlatformActor::Rotate(float t)
{
	auto CurrentRotation = GetActorRotation();
	CurrentRotation.Pitch = InitialRotation.Pitch + AmplitudeRotate * FMath::Sin(0.1 + FrequancyRotate * t);
	CurrentRotation.Yaw = InitialRotation.Yaw + AmplitudeRotate * FMath::Sin(0.1 + FrequancyRotate * t);
	CurrentRotation.Roll = InitialRotation.Roll + AmplitudeRotate * FMath::Sin(0.1 + FrequancyRotate * t);
	SetActorRotation(CurrentRotation);
}

