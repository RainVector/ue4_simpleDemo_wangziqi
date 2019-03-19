// Fill out your copyright notice in the Description page of Project Settings.

#include "CubePawn.h"
#include <windows.h>

InfoCube Cube;
// Sets default values
ACubePawn::ACubePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACubePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector cubeLocation;
	cubeLocation = GetPawnViewLocation();

	Cube.halfHeight = GetSimpleCollisionHalfHeight();
	Cube.x = cubeLocation.X;
	Cube.y = cubeLocation.Y;
	Cube.z = cubeLocation.Z;
	WCHAR buffer[100];
	swprintf(buffer,L"the cube is at (%f, %f, %f).\r\n", cubeLocation.X, cubeLocation.Y, cubeLocation.Z);
	OutputDebugString(buffer);
}

// Called to bind functionality to input
void ACubePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

