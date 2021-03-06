// Unpayed Co © Copyright Protected by the USA law © 2018 ALL RIGHT RESERVED © the ownership of this material without a written permission by hand or by e-mail sent by the Unpayed .Co OFFICIALS or the direct OWNER of this exact or copy of this work is clear infringement of copyright and is punishable by law unless 

#pragma once
#include "Components/PrimitiveComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME00_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere,
		Category ="LineTrace" ,
		meta = (ClampMin = "0.0", ClampMax = "1000.0", UIMin = "0.0", UIMax = "1000.0"))

	float Reach = 100.F;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;
	void Grab();
	void Release();
	void FindPhysicsHandleComponent();
	void SetupInputComponent();
	FHitResult GetFirstPhysicsBodyInReach();
	FVector GetReachLineEnd();
	FVector GetReachLineStart();
	void DrawDebugLineAtPlayerPosition();

	UPROPERTY(EditAnywhere,
		Category = "LOGS")
		bool bLogLineTraceHit =false;
	UPROPERTY(EditAnywhere,
		Category = "LOGS")
	    bool bLogPosRot = false;
	UPROPERTY(EditAnywhere,
		Category = "LOGS")
	    bool bLogInputCompMiss = true;
	UPROPERTY(EditAnywhere,
		Category = "LOGS")
	    bool bLogInputCompFound = true;
	UPROPERTY(EditAnywhere,
		Category = "LOGS")
	    bool bLogPhysicsCompMiss=true;
	UPROPERTY(EditAnywhere,
		Category = "LOGS")
	    bool bLogGrabPress = true;
	UPROPERTY(EditAnywhere,
		Category = "LOGS") 
	    bool bLogGrabReleased = true;

};