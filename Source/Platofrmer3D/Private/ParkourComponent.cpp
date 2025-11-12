// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourComponent.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogParkourComponent, All, All);
// Sets default values for this component's properties
UParkourComponent::UParkourComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	WallJumpSphereComponent = CreateDefaultSubobject<USphereComponent>("WallJumpSphereComponent");
	WallJumpSphereComponent->SetSphereRadius(50.0f);
	WallJumpSphereComponent->SetGenerateOverlapEvents(true);
	WallJumpSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WallJumpSphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	WallJumpSphereComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	WallJumpSphereComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);

	WallJumpSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UParkourComponent::OnWallJumpSphereBeginOverlap);
	WallJumpSphereComponent->OnComponentEndOverlap.AddDynamic(this, &UParkourComponent::OnWallJumpSphereEndOverlap);
	// ...
}


// Called when the game starts
void UParkourComponent::BeginPlay()
{
	Super::BeginPlay();
	WallJumpSphereComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	// ...
	
}


// Called every frame
void UParkourComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UParkourComponent::WallJump()
{

}

void UParkourComponent::OnWallJumpSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogParkourComponent, Log, TEXT("OverlapBegin"))

			bDoubleJumpPossible = JumpMaxCount > JumpCount;


}

void UParkourComponent::OnWallJumpSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogParkourComponent, Log, TEXT("OverlapEnd"))

		bDoubleJumpPossible = false;


}

