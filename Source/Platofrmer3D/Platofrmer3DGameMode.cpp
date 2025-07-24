// Copyright Epic Games, Inc. All Rights Reserved.

#include "Platofrmer3DGameMode.h"
#include "Platofrmer3DCharacter.h"
#include "UObject/ConstructorHelpers.h"

APlatofrmer3DGameMode::APlatofrmer3DGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
