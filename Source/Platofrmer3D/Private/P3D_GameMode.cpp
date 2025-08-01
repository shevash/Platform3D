// Fill out your copyright notice in the Description page of Project Settings.


#include "P3D_GameMode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "FinishLevelActor/FinishLevelActor.h"
#include "HUD/P3D_HUD.h"

DEFINE_LOG_CATEGORY_STATIC(LogP3DGameMode, All, All)
AP3D_GameMode::AP3D_GameMode()
{

}

void AP3D_GameMode::BeginPlay()
{
	TArray<AActor*> FinishActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFinishLevelActor::StaticClass(), FinishActors);
	AFinishLevelActor* FinishActor = Cast<AFinishLevelActor>(FinishActors[0]);
	FinishActor->OnFinish.AddUObject(this, &AP3D_GameMode::FinishLevel);
	GetWorld()->GetTimerManager().SetTimer(ClockTimerHandle,this,  &AP3D_GameMode::incrementSeconds,1.0f , true);


}

void AP3D_GameMode::incrementSeconds()
{
	Seconds++;
	OnIncrementSeconds.Broadcast(Seconds);
	UE_LOG(LogP3DGameMode, Log, TEXT("%d"), Seconds);
}

void AP3D_GameMode::FinishLevel()
{
	UE_LOG(LogP3DGameMode, Log, TEXT("Finish"));
	auto PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AP3D_HUD* HUD = Cast<AP3D_HUD>(PC->GetHUD());
	GetWorld()->GetTimerManager().ClearTimer(ClockTimerHandle);
	HUD->AddFinishLevelWidgetToViewport();
	PC->bShowMouseCursor = true;
	SetPause(PC);
	//APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	//UKismetSystemLibrary::QuitGame(GetWorld(),PC, EQuitPreference::Quit, true);
}

int32 AP3D_GameMode::GetTime()
{
	return Seconds;
}