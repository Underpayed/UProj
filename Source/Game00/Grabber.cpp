// Unpayed Co © Copyright Protected by the USA law © 2018 ALL RIGHT RESERVED © the ownership of this material without a written permission by hand or by e-mail sent by the Unpayed .Co OFFICIALS or the direct OWNER of this exact or copy of this work is clear infringement of copyright and is punishable by law unless 

#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGrabber::Grab() {
	if (bLogGrabPress)
	{
		UE_LOG(LogTemp, Warning, TEXT(" Grab Pressed ."))
	}
}

void UGrabber::Release() {
	if (bLogGrabReleased) {
		UE_LOG(LogTemp, Warning, TEXT(" Grab Released ."))
	}
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	// look for a physicHandle
	{
		PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
		if (PhysicsHandle) {
			//
		}
		else {
			if (bLogPhysicsCompMiss)
			{

				UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component ."), *GetOwner()->GetName())

			}
		}
	}

	// look for an InputComponent
	{
		InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
		if (InputComponent) {
			if (bLogInputCompFound)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s Input component found ."), *GetOwner()->GetName())
					InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
				InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
			}

		}
		else {
			if (bLogInputCompMiss)
			{
				UE_LOG(LogTemp, Error, TEXT("%s missing Input component ."), *GetOwner()->GetName())
			}
		}
	}
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	// get view point rotation and location
	{
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
			PlayerViewPointLocation,
			PlayerViewPointRotation
		);
		if(bLogPosRot)
		UE_LOG(LogTemp, Warning, TEXT("Position : ( %s ) ,Rotation : ( %s ) ."),
			*PlayerViewPointLocation.ToString(),
			*PlayerViewPointRotation.ToString());
	}

	//get LineTraceEnd
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

    // draw line for debug
	{
		UKismetSystemLibrary::DrawDebugLine(
			GetWorld(),
			PlayerViewPointLocation,
			LineTraceEnd,
			FColor(209, 18, 126),
			0.f,
			10.f
		);
	}

	// Collision 
	{
		FHitResult Hit;

		FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

		GetWorld()->LineTraceSingleByObjectType(
			Hit,
			PlayerViewPointLocation,
			LineTraceEnd,
			FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
			TraceParameters
		);

		AActor* ActorHit = Hit.GetActor();
		if (ActorHit)
		{
			if (bLogLineTraceHit) 
			{
				UE_LOG(LogTemp, Warning, TEXT("Line Trace Hit: %s"), *(ActorHit->GetName()))
			}
		}
	}
}

