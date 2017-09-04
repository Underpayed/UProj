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
	// Open door 95 degree instantly and Return whether successful 
	bool bRotationState = GetOwner()->SetActorRotation(FRotator(0.0f, 95.0f, 0.0f));
	FString ObjectName = GetOwner()->GetName();
	//  ^  ^  ^ Log if successful ^  ^  ^ 
	UE_LOG(LogTemp, Warning, TEXT(" opening %s was a %s"), *ObjectName,bRotationState ? TEXT("Success") : TEXT("Failure"));
	

	// ...
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

