// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HandCharacter.generated.h"
extern FRotator skelToWorld;
extern FVector indexLocation[4];
extern FVector thumbLocation[4];
extern FVector middleLocation[4];
extern FVector ringLocation[4];
extern FVector littleLocation[4];
UCLASS()
class HAND_API AHandCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHandCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
