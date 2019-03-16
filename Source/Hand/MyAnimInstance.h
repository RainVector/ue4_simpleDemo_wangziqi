// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
FRotator caliThumb1(float *angle);
FRotator caliThumb3(float *angle);
FRotator caliIndex1(float *angle);
FRotator caliIndex2(float *angle);
FRotator caliIndex3(float *angle);
FRotator caliMiddle1(float *angle);
FRotator caliMiddle2(float *angle);
FRotator caliMiddle3(float *angle);
FRotator caliRing1(float *angle);
FRotator caliRing2(float *angle);
FRotator caliRing3(float *angle);
FRotator caliLittle1(float *angle);
FRotator caliLittle2(float *angle);
FRotator caliLittle3(float *angle);
UCLASS()
class HAND_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Animation")
		FRotator ChangeThumb1()  const;

	UFUNCTION(BlueprintCallable, Category = "Animation")
		FRotator ChangeThumb3()  const;

	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (NotBlueprintThreadSafe))
		FRotator ChangeIndex1()  const;

	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (NotBlueprintThreadSafe))
		FRotator ChangeIndex2()  const;

	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (NotBlueprintThreadSafe))
		FRotator ChangeIndex3()  const;


	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (NotBlueprintThreadSafe))
		FRotator ChangeMiddle1()  const;

	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (NotBlueprintThreadSafe))
		FRotator ChangeMiddle2()  const;

	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (NotBlueprintThreadSafe))
		FRotator ChangeMiddle3()  const;

	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (NotBlueprintThreadSafe))
		FRotator ChangeRing1()  const;

	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (NotBlueprintThreadSafe))
		FRotator ChangeRing2()  const;

	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (NotBlueprintThreadSafe))
		FRotator ChangeRing3()  const;

	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (NotBlueprintThreadSafe))
		FRotator ChangeLittle1()  const;

	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (NotBlueprintThreadSafe))
		FRotator ChangeLittle2()  const;


	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (NotBlueprintThreadSafe))
		FRotator ChangeLittle3()  const;


	
	
	
};
