// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TFGGameMode.h"
#include "TFGCharacter.h"
#include "GOAP_NPCPlayerController.h"
#include "UObject/ConstructorHelpers.h"

ATFGGameMode::ATFGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = AGOAP_NPCPlayerController::StaticClass();

}
