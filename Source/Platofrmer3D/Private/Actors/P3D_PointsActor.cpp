// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/P3D_PointsActor.h"
#include "Character/P3D_Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogPointActor,All,All)
// Sets default values
AP3D_PointsActor::AP3D_PointsActor()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxCollision->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	BoxCollision->AttachTo(RootComponent);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AP3D_PointsActor::OnCharBeginOverlap);

	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AP3D_PointsActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AP3D_PointsActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AP3D_PointsActor::OnCharBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AP3D_Character>(OtherActor))
	{
		auto Player = Cast<AP3D_Character>(OtherActor);
		Player->AddPointsToScore(Points);
	}
}

