// Fill out your copyright notice in the Description page of Project Settings.


#include "P3D_GameInstance.h"

void UP3D_GameInstance::AddScore(int32 Points)
{ 
	Score += Points; 
	UpdateScore.Broadcast(Score);
}