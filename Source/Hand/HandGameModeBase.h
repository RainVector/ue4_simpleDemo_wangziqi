// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HandGameModeBase.generated.h"

/**
 * 
 */
extern ENGINE_API class UEngine*			GEngine;

UCLASS()
class HAND_API AHandGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AHandGameModeBase();
	
};
