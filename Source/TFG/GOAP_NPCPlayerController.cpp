// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAP_NPCPlayerController.h"
#include "GOAPController.h"
#include "GOAPKeyDoor.h"
#include "Kismet/GameplayStatics.h"

void AGOAP_NPCPlayerController::DestroyPawnByName(FString ActorName, bool bDestroyControllerToo)
{

	TArray<AActor*> AllPawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawn::StaticClass(), AllPawns);

	for (AActor* Actor : AllPawns)
	{
		if (Actor->GetName().Contains(ActorName))
		{
			APawn* FoundPawn = Cast<APawn>(Actor);
			AController* OwningController = FoundPawn ? FoundPawn->GetController() : nullptr;

			UE_LOG(LogTemp, Warning, TEXT("DestroyPawnByName: destroying pawn %s (controller destroy = %s)"),
				*Actor->GetName(), bDestroyControllerToo ? TEXT("true") : TEXT("false"));

			FoundPawn->Destroy();

			if (bDestroyControllerToo && OwningController)
				OwningController->Destroy();

			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("DestroyPawnByName: no pawn found matching '%s'"), *ActorName);
}

void AGOAP_NPCPlayerController::SetDoorJammed(FString DoorName, bool bJammed)
{
	TArray<AActor*> Doors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGOAPKeyDoor::StaticClass(), Doors);

	for (AActor* Actor : Doors)
	{
		if (Actor->GetName().Contains(DoorName))
		{
			Cast<AGOAPKeyDoor>(Actor)->bJammed = bJammed;
			UE_LOG(LogTemp, Warning, TEXT("SetDoorJammed: %s jammed = %s"),
				*Actor->GetName(), bJammed ? TEXT("true") : TEXT("false"));
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("SetDoorJammed: no door found matching '%s'"), *DoorName);
}
