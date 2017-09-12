// Unpayed Co © Copyright Protected by the USA law © 2018 ALL RIGHT RESERVED © the ownership of this material without a written permission by hand or by e-mail sent by the Unpayed .Co OFFICIALS or the direct OWNER of this exact or copy of this work is clear infringement of copyright and is punishable by law unless 

#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	AOpener = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	StartTimerByPressurePlate();
	CloseDoorByDelay();
}

// Start Timer when stepped in a pressure Plate
void UOpenDoor::StartTimerByPressurePlate()
{
	if (PressurePlate->IsOverlappingActor(AOpener))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
}
// check if it's time to close the door and do Close it
void UOpenDoor::CloseDoorByDelay()
{
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}
}
// OpenDoor
bool UOpenDoor::OpenDoor()
{
	return GetOwner()->SetActorRotation(FRotator(0.0f, OpeningAngle, 0.0f));

}
// Close the Door
bool UOpenDoor::CloseDoor()
{
	return GetOwner()->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}