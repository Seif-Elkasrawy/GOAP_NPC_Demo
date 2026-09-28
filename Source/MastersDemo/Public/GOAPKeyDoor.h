// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GOAPBroadcastable.h"
#include "GOAPKeyDoor.generated.h"

UCLASS()
class MASTERSDEMO_API AGOAPKeyDoor : public AActor, public IGOAPBroadcastable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGOAPKeyDoor();

	/** True once a key has been placed at this door's first location. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = KeyDoor)
	bool socketAFilled = false;

	/** True once a key has been placed at this door's second location. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = KeyDoor)
	bool socketBFilled = false;

	/**
	 * Name of the atom to broadcast once unlocked. Kept per-instance so
	 * multiple doors can each announce something distinct, e.g.
	 * "doorAOpen" / "doorBOpen".
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KeyDoor)
	FString openAtomName = TEXT("doorOpen");

	/** Called by the PlaceKey action (or equivalent) once its key physically reaches socket A. */
	UFUNCTION(BlueprintCallable, Category = KeyDoor)
	void FillSocketA();

	/** Called by the PlaceKey action (or equivalent) once its key physically reaches socket B. */
	UFUNCTION(BlueprintCallable, Category = KeyDoor)
	void FillSocketB();

	/**
	 * Fired exactly once, the moment both sockets become filled. Implement
	 * this in the KeyDoor Blueprint to do whatever "the door opens" should
	 * look like (Destroy Actor, play an open animation, etc.) - nothing
	 * native calls this from outside FillSocketA/FillSocketB, so no GOAP
	 * action needs to "perform" opening the door itself.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = KeyDoor)
	void OnUnlocked();

	// IGOAPBroadcastable
	virtual bool IsConditionMet_Implementation() const override;
	virtual FAtom GetBroadcastAtom_Implementation() const override;

private:

	/** Guards OnUnlocked so it only ever fires once, however many times FillSocketA/B get called afterward. */
	bool hasFiredUnlockEvent = false;

	/** Checks IsUnlocked() and fires OnUnlocked() the first time it becomes true. */
	void CheckAndFireUnlock();
};
