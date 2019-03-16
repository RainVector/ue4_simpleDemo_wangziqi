// Fill out your copyright notice in the Description page of Project Settings.

#include "HandCharacter.h"
#include <Windows.h>

// Sets default values
FVector handLocation;

FVector thumbLocation[4];
FVector indexLocation[4];
FVector middleLocation[4];
FVector ringLocation[4];
FVector littleLocation[4];
FRotator skelToWorld = FRotator(0., -108., 50.);
AHandCharacter::AHandCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHandCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	/*indexLocation[0] = skelToWorld.RotateVector(indexLocation[0]);
	indexLocation[2] = skelToWorld.RotateVector(indexLocation[2]);*/
	//FVector temp = (FVector)(GetWorld()->OriginLocation);
	
	
	
}

// Called every frame
void AHandCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	handLocation = GetActorLocation();
	//WCHAR buffer[100];
	//swprintf(buffer, L"the hand is at (%f, %f, %f).\r\n", handLocation.X, handLocation.Y, handLocation.Z);
	//OutputDebugString(buffer);
	/*WCHAR buffer[100];
	swprintf(buffer, L"the index3 is at (%f, %f, %f).\r\n", indexLocation[2].X, indexLocation[2].Y, indexLocation[2].Z);
	OutputDebugString(buffer);*/
	

	//indexLocation[1] = 
	/*WCHAR buffer[100];
	swprintf(buffer, L"the index1 is at (%f, %f, %f).\r\n", indexLocation[0].X, indexLocation[0].Y, indexLocation[0].Z);
	OutputDebugString(buffer);*/

	/*auto BoneIdx = SkeletalMeshComponent->GetBoneIndex(TEXT("SheKRArm2"));
	SkeletalMeshComponent->LocalAtoms[BoneIdx].AddToTranslation(FVector(100, 100, 100));
	SkeletalMeshComponent->FillSpaceBases();*/
}

// Called to bind functionality to input
void AHandCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

