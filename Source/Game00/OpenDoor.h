// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseRequest);
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAME00_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool OpenDoor();
	bool CloseDoor();
	float GetTotalMassOfActorsOnPlate();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartTimerByPressurePlate();

	void CloseDoorByDelay();

private:
	UPROPERTY(EditAnywhere)
		float OpeningAngle = 125.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume *PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.f;

	UPROPERTY(BlueprintAssignable)
		FOnOpenRequest OnOpenResquest;
	UPROPERTY(BlueprintAssignable)
		FOnCloseRequest OnCloseResquest;

		float LastDoorOpenTime;

		UInputComponent* InputComponent = nullptr;

};
