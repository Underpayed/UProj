// Unpayed Co © Copyright Protected by the USA law © 2018 ALL RIGHT RESERVED © the ownership of this material without a written permission by hand or by e-mail sent by the Unpayed .Co OFFICIALS or the direct OWNER of this exact or copy of this work is clear infringement of copyright and is punishable by law unless 

#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	ObjectOwner = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	

	// ...
	
}

// Open the Door
void UOpenDoor::OpenDoor()
{
	// Open door instantly
	bool bRotationState = ObjectOwner->SetActorRotation(FRotator(0.0f, OpeningAngle , 0.0f));
	
	// LOGisOFF OPENING DOOR
	//  ^  ^  ^ Log if successful ^  ^  ^ 
	//FString ObjectName = ObjectOwner.GetName();
	//  UE_LOG(LogTemp, Warning, TEXT(" opening %s was a %s ."), *ObjectName, bRotationState ? TEXT("Success") : TEXT("Failure"));
}

// Close the Door
void UOpenDoor::CloseDoor()
{
	// Close door instantly
	bool bRotationState = ObjectOwner->SetActorRotation(FRotator(0.0f,0.0f, 0.0f));

	// LOGisOFF CLOSING DOOR
	//  ^  ^  ^ Log if successful ^  ^  ^ 
	//FString ObjectName = ObjectOwner.GetName();
	//  UE_LOG(LogTemp, Warning, TEXT(" Closing %s was a %s ."), *ObjectName, bRotationState ? TEXT("Success") : TEXT("Failure"));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//Poll the trigger volume
	    // if pawn that opens is in the trigger volume 
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	//check if it's time to close the door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}
	// ...
}