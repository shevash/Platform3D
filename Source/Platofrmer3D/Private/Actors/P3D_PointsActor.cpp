// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/P3D_PointsActor.h"
#include "Character/P3D_Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogPointActor,All,All)
// Sets default values
AP3D_PointsActor::AP3D_PointsActor()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxCollision->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	BoxCollision->AttachTo(RootComponent);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AP3D_PointsActor::OnCharBeginOverlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetCollisionProfileName(FName("NoCollision"));
	StaticMesh->AttachTo(RootComponent);

	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AP3D_PointsActor::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(RotateTimer, this, &AP3D_PointsActor::RotateMesh, 0.01f, true);
}

void AP3D_PointsActor::RotateMesh()
{
	StaticMesh->AddLocalRotation(FRotator(0.0f, 1.0f, 0.0f));
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
		this->Destroy();
	}
}

