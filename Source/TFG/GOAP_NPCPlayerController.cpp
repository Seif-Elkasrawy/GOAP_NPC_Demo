// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAP_NPCPlayerController.h"
#include "GOAPController.h"
#include "GOAPKeyDoor.h"
#include "Kismet/GameplayStatics.h"

void AGOAP_NPCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindKey(EKeys::K, IE_Pressed, this, &AGOAP_NPCPlayerController::KillNearestAgent);
	InputComponent->BindKey(EKeys::J, IE_Pressed, this, &AGOAP_NPCPlayerController::JamNearestDoor);
	InputComponent->BindKey(EKeys::G, IE_Pressed, this, &AGOAP_NPCPlayerController::CycleDebugDraw);
	InputComponent->BindKey(EKeys::H, IE_Pressed, this, &AGOAP_NPCPlayerController::ReloadLevel);
}

void AGOAP_NPCPlayerController::CycleDebugDraw()
{
	IConsoleVariable* var = IConsoleManager::Get().FindConsoleVariable(TEXT("GOAP.DebugDraw"));
	if (var == nullptr)
		return;

	const int32 next = (var->GetInt() + 1) % 3; // 0 -> 1 -> 2 -> 0
	var->Set(next, ECVF_SetByConsole);
}

void AGOAP_NPCPlayerController::KillNearestAgent()
{
	APawn* playerPawn = GetPawn();
	if (playerPawn == nullptr)
		return;

	TArray<AActor*> pawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawn::StaticClass(), pawns);

	APawn* nearest = nullptr;
	float bestDistSq = TNumericLimits<float>::Max();

	for (AActor* actor : pawns)
	{
		APawn* pawn = Cast<APawn>(actor);
		if (pawn == nullptr) continue;

		// Only GOAP agents count. The player's pawn has a player controller, so it is skipped here too.
		if (Cast<AGOAPController>(pawn->GetController()) == nullptr) continue;

		const float distSq = FVector::DistSquared(playerPawn->GetActorLocation(), pawn->GetActorLocation());
		if (distSq < bestDistSq)
		{
			bestDistSq = distSq;
			nearest = pawn;
		}
	}

	if (nearest == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("KillNearestAgent: no GOAP agent found"));
		return;
	}

	AController* controller = nearest->GetController();
	UE_LOG(LogTemp, Warning, TEXT("KillNearestAgent: destroying %s (dist %.0f)"),
		*nearest->GetName(), FMath::Sqrt(bestDistSq));

	nearest->Destroy();
	if (controller != nullptr) controller->Destroy();
}

void AGOAP_NPCPlayerController::JamNearestDoor()
{
	APawn* playerPawn = GetPawn();
	if (playerPawn == nullptr)
		return;

	TArray<AActor*> doors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGOAPKeyDoor::StaticClass(), doors);

	AGOAPKeyDoor* nearest = nullptr;
	float bestDistSq = TNumericLimits<float>::Max();

	for (AActor* actor : doors)
	{
		AGOAPKeyDoor* door = Cast<AGOAPKeyDoor>(actor);
		if (door == nullptr) continue;

		const float distSq = FVector::DistSquared(playerPawn->GetActorLocation(), door->GetActorLocation());
		if (distSq < bestDistSq)
		{
			bestDistSq = distSq;
			nearest = door;
		}
	}

	if (nearest == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("JamNearestDoor: no GOAP KeyDoor found"));
		return;
	}

	nearest->bJammed = !nearest->bJammed;

	UE_LOG(LogTemp, Warning, TEXT("JamNearestDoor: %s jammed = %s"),
		*nearest->GetName(), nearest->bJammed ? TEXT("true") : TEXT("false"));
}

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

void AGOAP_NPCPlayerController::ReloadLevel()
{
	const FString levelName = UGameplayStatics::GetCurrentLevelName(this, true); // true strips the PIE prefix
	UGameplayStatics::OpenLevel(this, FName(*levelName));
}
