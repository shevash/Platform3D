// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourComponent.h"
#include "GameFramework/Character.h"
#include "Character/P3D_Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY_STATIC(LogParkourComponent, All, All);
// Sets default values for this component's properties
UParkourComponent::UParkourComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;



}


// Called when the game starts
void UParkourComponent::BeginPlay()
{
	Super::BeginPlay();
	check(GetWorld());
	check(GetOwner());
	auto Player = Cast<AP3D_Character>(GetOwner());
	Player->JumpMaxCount = JumpMaxCount;

	WallJumpSphereComponent = NewObject<USphereComponent>(GetOwner(),"WallJumpSphereComponent");
	GetOwner()->AddInstanceComponent(WallJumpSphereComponent);
	WallJumpSphereComponent->SetSphereRadius(50.0f);
	WallJumpSphereComponent->SetGenerateOverlapEvents(true);
	WallJumpSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WallJumpSphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	WallJumpSphereComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	WallJumpSphereComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	WallJumpSphereComponent->bHiddenInGame = false;
	WallJumpSphereComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	WallJumpSphereComponent->RegisterComponentWithWorld(GetOwner()->GetWorld());
	WallJumpSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UParkourComponent::OnWallJumpSphereBeginOverlap);
	WallJumpSphereComponent->OnComponentEndOverlap.AddDynamic(this, &UParkourComponent::OnWallJumpSphereEndOverlap);


	WallClimbPermitBoxComponent = NewObject<UBoxComponent>(GetOwner(),"WallClimbPermitBoxComponent");
	GetOwner()->AddInstanceComponent(WallClimbPermitBoxComponent);
	WallClimbPermitBoxComponent->SetRelativeLocation(FVector(60.0f, 0.0f, 80.0f));
	WallClimbPermitBoxComponent->SetBoxExtent(FVector(40.0f, 25.0f, 32.0f));
	WallClimbPermitBoxComponent->SetGenerateOverlapEvents(true);
	WallClimbPermitBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WallClimbPermitBoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	WallClimbPermitBoxComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	WallClimbPermitBoxComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	WallClimbPermitBoxComponent->bHiddenInGame = false;
	WallClimbPermitBoxComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	WallClimbPermitBoxComponent->RegisterComponentWithWorld(GetOwner()->GetWorld());
	WallClimbPermitBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UParkourComponent::OnWallClimbPermitBoxBeginOverlap);
	WallClimbPermitBoxComponent->OnComponentEndOverlap.AddDynamic(this, &UParkourComponent::OnWallClimbPermitBoxEndOverlap);


	WallClimbDeniedBoxComponent = NewObject<UBoxComponent>(GetOwner(), "WallClimbDeniedBoxComponent");
	GetOwner()->AddInstanceComponent(WallClimbDeniedBoxComponent);
	WallClimbDeniedBoxComponent->SetRelativeLocation(FVector(50.0f, 0.0f, 120.0f));
	WallClimbDeniedBoxComponent->SetBoxExtent(FVector(100.0f, 100.0f, 5.0f));
	WallClimbDeniedBoxComponent->SetGenerateOverlapEvents(true);
	WallClimbDeniedBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WallClimbDeniedBoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	WallClimbDeniedBoxComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	WallClimbDeniedBoxComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	WallClimbDeniedBoxComponent->bHiddenInGame = false;
	WallClimbDeniedBoxComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	WallClimbDeniedBoxComponent->RegisterComponentWithWorld(GetOwner()->GetWorld());
	WallClimbDeniedBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UParkourComponent::OnWallClimbDeniedBoxBeginOverlap);
	WallClimbDeniedBoxComponent->OnComponentEndOverlap.AddDynamic(this, &UParkourComponent::OnWallClimbDeniedBoxEndOverlap);
}


// Called every frame
void UParkourComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UParkourComponent::WallJump()
{
	
	auto Player = Cast<AP3D_Character>(GetOwner());
	if (bHoldingOn == true)
	{
		Player->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		Player->bFlying = false;
		bHoldingOn = false;
		Player->SetActorLocation((Player->GetActorLocation() + Player->GetActorForwardVector()*200) + FVector(0.0f, 0.0f, 300.0f));
		return;
	}

	if (bPermitToClimb && !bDeniedToClimb)
	{
		ClimbUp();
		return;
	}
	

	if (CanDoubleJump() && Player->GetCharacterMovement()->IsFalling())
	{
		
		UE_LOG(LogParkourComponent, Log, TEXT("DoubleJump"))
		Player->ACharacter::Jump();
		IncrementJumpCount();
		bDoubleJumpPossible = false;
		return;
	}
	if(CanClimb()){
	if (Player->JumpCurrentCount == 0)
	{
		UE_LOG(LogParkourComponent, Log, TEXT("Jump"))
		Player->ACharacter::Jump();
		
	}
	}
}

void UParkourComponent::OnWallJumpSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogParkourComponent, Log, TEXT("OverlapBegin"))

	bDoubleJumpPossible = JumpMaxCount > JumpCount;
	bNearWall = true;

}

void UParkourComponent::OnWallJumpSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogParkourComponent, Log, TEXT("OverlapEnd"))

	bDoubleJumpPossible = false;
	bNearWall = false;


}

void UParkourComponent::OnWallClimbPermitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogParkourComponent, Log, TEXT("PermitOverlapBegin"))
	bPermitToClimb = true;
	auto Player = Cast<AP3D_Character>(GetOwner());
	PermitActor = OtherActor;
	if (Player->GetCharacterMovement()->IsFalling()) HoldOnLedge();
	WallClimbPermitBoxHitResult = SweepResult;

}


void UParkourComponent::OnWallClimbPermitBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogParkourComponent, Log, TEXT("PermitOverlapEnd"))
		bPermitToClimb = false;
	PermitActor = nullptr;
}

void UParkourComponent::OnWallClimbDeniedBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogParkourComponent, Log, TEXT("DeniedOverlapBegin"))
	bDeniedToClimb = true;
	DeniedActor = OtherActor;
}

void UParkourComponent::OnWallClimbDeniedBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogParkourComponent, Log, TEXT("DeniedOverlapEnd"))
	bDeniedToClimb = false;
	DeniedActor = nullptr;
}

void UParkourComponent::ResetJump()
{
	check(this)
	JumpCount = 0;
	bDoubleJumpPossible = bNearWall;
	WallClimbPermitBoxComponent->SetGenerateOverlapEvents(true);
	WallClimbDeniedBoxComponent->SetGenerateOverlapEvents(true);
}

void UParkourComponent::ClimbUp()
{
	UE_LOG(LogParkourComponent, Log, TEXT("ClimbUp"))
		
}

void UParkourComponent::HoldOnLedge()
{
	if (bDeniedToClimb) return;
	auto Player = Cast<AP3D_Character>(GetOwner());
	Player->GetCharacterMovement()->DisableMovement();
	//Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	Player->bFlying = true;
	WallClimbPermitBoxComponent->SetGenerateOverlapEvents(false);
	WallClimbDeniedBoxComponent->SetGenerateOverlapEvents(false);
	bHoldingOn = true;
	Player->AttachToActor(PermitActor, FAttachmentTransformRules::KeepWorldTransform);
	UE_LOG(LogParkourComponent, Log, TEXT("HoldOnLedge"))
		HoldingOnCharacterPosition();
}

void UParkourComponent::HoldingOnCharacterPosition()
{
	auto Player = Cast<AP3D_Character>(GetOwner());
	auto ForwardLineStart = Player->GetActorLocation()+Player->GetActorForwardVector()*30;
	auto ForwardLineEnd = Player->GetActorLocation()+Player->GetActorForwardVector()*500;
	auto LeftLineStart = Player->GetActorLocation();
	auto LeftLineEnd = Player->GetActorLocation() - Player->GetActorRightVector() *  500;
	auto RightLineStart = Player->GetActorLocation();
	auto RightLineEnd = Player->GetActorLocation() + Player->GetActorRightVector() * 500;
	auto UpLineStart = Player->GetActorLocation()+Player->GetActorForwardVector()*100 + FVector(0.0, 0.0, 500.0);
	auto UpLineEnd = Player->GetActorLocation() + Player->GetActorForwardVector() * 100;

	FHitResult ForwardLineResult;
	FHitResult LeftLineResult;
	FHitResult RightLineResult;
	FHitResult UpLineResult;

	GetWorld()->LineTraceSingleByChannel(ForwardLineResult, ForwardLineStart, ForwardLineEnd, ECollisionChannel::ECC_Visibility);
	GetWorld()->LineTraceSingleByChannel(LeftLineResult, LeftLineStart, LeftLineEnd, ECollisionChannel::ECC_WorldDynamic);
	GetWorld()->LineTraceSingleByChannel(RightLineResult, RightLineStart, RightLineEnd, ECollisionChannel::ECC_WorldDynamic);

	
	DrawDebugLine(GetWorld(), ForwardLineStart, ForwardLineEnd, FColor::Red, false, 5,0,3);
	DrawDebugSphere(GetWorld(), ForwardLineResult.ImpactPoint, 5, 8, FColor::Red, false, 5, 0, 3);


	FVector DesiredNormal = -ForwardLineResult.Normal;
	FRotator NewRotation = DesiredNormal.Rotation();
	NewRotation.Pitch = 0.f;
	NewRotation.Roll = 0.f;
	Player->SetActorRotation(NewRotation);
	Player->SetActorLocation(ForwardLineResult.ImpactPoint+ ForwardLineResult.Normal *30);
	GetWorld()->LineTraceSingleByChannel(UpLineResult, UpLineStart, UpLineEnd, ECollisionChannel::ECC_Visibility);
	DrawDebugLine(GetWorld(), UpLineStart, UpLineEnd, FColor::Red, false, 5, 0, 3);
	DrawDebugSphere(GetWorld(), UpLineResult.ImpactPoint, 5, 8, FColor::Red, false, 5, 0, 3);

	//Player->SetActorLocation(FVector(Player->GetActorLocation().X, Player->GetActorLocation().Y, UpLineResult.ImpactPoint.Z));
	//UE_LOG(LogParkourComponent, Log, TEXT("%s"), ToString(ForwardLineResult.ImpactPoint))



}

