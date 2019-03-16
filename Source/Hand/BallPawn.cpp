// Fill out your copyright notice in the Description page of Project Settings.

#include "BallPawn.h"
#include <windows.h>

// Sets default values

FVector ballLocation;
ABallPawn::ABallPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABallPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABallPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*static float temp=0;
	temp++;
	ControlInputVector = FVector(0, 0, temp);*/
	//Internal_AddMovementInput(FVector(0, 0, 10));
	ballLocation = GetPawnViewLocation();
	/*WCHAR buffer[100];
	swprintf(buffer,L"the ball is at (%f, %f, %f).\r\n", ballLocation.X, ballLocation.Y, ballLocation.Z);
	OutputDebugString(buffer);*/

}

// Called to bind functionality to input
void ABallPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

