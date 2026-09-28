// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GOAP_NPCPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TFG_API AGOAP_NPCPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UFUNCTION(Exec)
	void DestroyPawnByName(FString ActorName, bool bDestroyControllerToo = false);
};
