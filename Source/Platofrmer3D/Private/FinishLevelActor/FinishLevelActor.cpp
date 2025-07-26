// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishLevelActor/FinishLevelActor.h"

DEFINE_LOG_CATEGORY_STATIC(LogFinishLevelActor, All, All)
AFinishLevelActor::AFinishLevelActor()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxCollision->SetBoxExtent(FVector(300.0f, 300.0f, 300.f));
	BoxCollision->AttachTo(RootComponent);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AFinishLevelActor::test);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFinishLevelActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFinishLevelActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFinishLevelActor::test(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	OnFinish.Broadcast();
}