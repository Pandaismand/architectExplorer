// Fill out your copyright notice in the Description page of Project Settings.


#include "VRCharakter.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "HeadMountedDisplay.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AVRCharakter::AVRCharakter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	VRRoot->SetupAttachment(GetRootComponent());


	HMDCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("HMDCamera"));
	HMDCamera->SetupAttachment(VRRoot);

	VRRoot->RelativeLocation.Set(0.f, 0.f, -93.00f);

	DestinationMarker = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DestinationMarker"));
	DestinationMarker->SetupAttachment(GetRootComponent());

	
}

// Called when the game starts or when spawned
void AVRCharakter::BeginPlay()
{
	Super::BeginPlay();
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Floor);
}

// Called every frame
void AVRCharakter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewHMDCameraOffset = HMDCamera->GetComponentLocation() - GetActorLocation();
	NewHMDCameraOffset.Z = 0;
	AddActorWorldOffset(NewHMDCameraOffset);
	VRRoot->AddWorldOffset(-NewHMDCameraOffset);

	
	update_teleport_marker();
	


}

// Called to bind functionality to input
void AVRCharakter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AVRCharakter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Strafe"), this, &AVRCharakter::StrafeRight);
	

}

void AVRCharakter::MoveForward(float throttle)
{
	AddMovementInput(throttle *  HMDCamera->GetForwardVector());
}

void AVRCharakter::StrafeRight(float throttle)
{
	AddMovementInput(throttle *  HMDCamera->GetRightVector());
}

void AVRCharakter::update_teleport_marker()
{
	FHitResult HitResult;
	FVector StartLocation = HMDCamera->GetComponentLocation();
	//FVector LookDirection = HMDCamera->GetForwardVector();
	FVector EndLocation = StartLocation + HMDCamera->GetForwardVector() * LineTraceRange;

    

	bool bHit = GetWorld()->LineTraceSingleByChannel
			(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility
			);
		
	if (bHit) {
		DestinationMarker->SetWorldLocation(HitResult.Location);
		DestinationMarker->SetVisibility(true);
	} else {
		DestinationMarker->SetVisibility(false);
	}

}