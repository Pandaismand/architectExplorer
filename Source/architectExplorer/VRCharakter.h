// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VRCharakter.generated.h"

UCLASS()
class ARCHITECTEXPLORER_API AVRCharakter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRCharakter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HMD Camera")
	class UCameraComponent* HMDCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRRoot")
	class USceneComponent* VRRoot;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* DestinationMarker;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void MoveForward(float throttle);
	void StrafeRight(float throttle);

	UPROPERTY(EditAnywhere)
	
	float LineTraceRange = 1000.0f;
	
	void update_teleport_marker();
	

};
