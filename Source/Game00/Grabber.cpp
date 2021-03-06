// Unpayed Co © Copyright Protected by the USA law © 2018 ALL RIGHT RESERVED © the ownership of this material without a written permission by hand or by e-mail sent by the Unpayed .Co OFFICIALS or the direct OWNER of this exact or copy of this work is clear infringement of copyright and is punishable by law unless 

#include "Grabber.h"
#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
	bLogPosRot = false;
	bLogLineTraceHit = false;
	bLogInputCompMiss = true;
	bLogInputCompFound = true;
	bLogPhysicsCompMiss = true;
	bLogGrabPress = true;
	bLogGrabReleased = true;
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!PhysicsHandle) { return; }
	if (PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
	DrawDebugLineAtPlayerPosition();
}

// Grab function
void UGrabber::Grab() {
	if (bLogGrabPress) {
		{
			UE_LOG(LogTemp, Warning, TEXT(" Grab Pressed ."))
		}
	}
     auto FHit = GetFirstPhysicsBodyInReach();
	 auto ComponentToGrab = FHit.GetComponent();
	 auto ActorHit = FHit.GetActor();
	 if (ActorHit) {
		 UE_LOG(LogTemp, Warning, TEXT(" Actor Hit %s ."),*ActorHit->GetName())
		 if (!PhysicsHandle) { return; }
		 PhysicsHandle->GrabComponent(
			 ComponentToGrab,
			 NAME_None,
			 ComponentToGrab->GetOwner()->GetActorLocation(),
			 false
		 );
	 }
}
// Release function
void UGrabber::Release() {
	if (bLogGrabReleased) 
	{
		UE_LOG(LogTemp, Warning, TEXT(" Grab Released ."))
	}
	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
}
// Find Physics Handle Component
void UGrabber::FindPhysicsHandleComponent() {
	// look for a physicHandle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle==nullptr) 
	{
		if (bLogPhysicsCompMiss)
		{
			UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component ."), *GetOwner()->GetName())
		}
	}
}
// Setup (assumed) InputComponent
void UGrabber::SetupInputComponent()
{
	
		InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
		if (InputComponent) {
			if (bLogInputCompFound)
			    {
				UE_LOG(LogTemp, Warning, TEXT("%s Input component found ."), *GetOwner()->GetName())
			    }
			InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
			InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
			}
		else {
			if (bLogInputCompMiss)
			{
				UE_LOG(LogTemp, Error, TEXT("%s missing Input component ."), *GetOwner()->GetName())
			}
		}
}
FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FHitResult Hit;

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetReachLineStart(),
		GetReachLineEnd(),
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
	return Hit;
}
FVector UGrabber::GetReachLineEnd() {
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	return GetReachLineStart() + PlayerViewPointRotation.Vector() * Reach;
}
FVector UGrabber::GetReachLineStart() {
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation;
}
void UGrabber::DrawDebugLineAtPlayerPosition()
{
	UKismetSystemLibrary::DrawDebugLine(
		GetWorld(),
		GetReachLineStart(),
		GetReachLineEnd(),
		FColor(255,0,0 ),
		0.f,
		10.f
	);
}