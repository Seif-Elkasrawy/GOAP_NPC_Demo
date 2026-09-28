// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAPKeyDoor.h"

// Sets default values
AGOAPKeyDoor::AGOAPKeyDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AGOAPKeyDoor::FillSocketA()
{
	socketAFilled = true;
	CheckAndFireUnlock();
}

void AGOAPKeyDoor::FillSocketB()
{
	socketBFilled = true;
	CheckAndFireUnlock();
}

void AGOAPKeyDoor::CheckAndFireUnlock() 
{
	if (!hasFiredUnlockEvent && IsConditionMet_Implementation())
	{
		hasFiredUnlockEvent = true;
		OnUnlocked();
	}
}

bool AGOAPKeyDoor::IsConditionMet_Implementation() const
{
	return socketAFilled && socketBFilled;
}

FAtom AGOAPKeyDoor::GetBroadcastAtom_Implementation() const
{
	FAtom atom;
	atom.name = openAtomName;
	atom.value = true;
	return atom;
}

