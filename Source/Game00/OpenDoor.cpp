// Unpayed Co © Copyright Protected by the USA law © 2018 ALL RIGHT RESERVED © the ownership of this material without a written permission by hand or by e-mail sent by the Unpayed .Co OFFICIALS or the direct OWNER of this exact or copy of this work is clear infringement of copyright and is punishable by law unless 

#include "OpenDoor.h"
#define OUT

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
	if (GetTotalMassOfActorsOnPlate() > 50.f) // TODO hard coded magic number
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
	OnOpenResquest.Broadcast();
	//return GetOwner()->SetActorRotation(FRotator(0.0f, OpeningAngle, 0.0f));
	return true;
}
// Close the Door
bool UOpenDoor::CloseDoor()
{
	OnCloseResquest.Broadcast();
	//return GetOwner()->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	return true;
}
float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	if (!PressurePlate) { return 0.f; };
	float TotalMass = 0.f;
	TArray<AActor*> ActorsOnPressurePlate ;
	PressurePlate->GetOverlappingActors(OUT ActorsOnPressurePlate);
	for (const auto& Actor : ActorsOnPressurePlate)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT(" %s On Pressure Plate"),*Actor->GetName())
	}
	return TotalMass;
}