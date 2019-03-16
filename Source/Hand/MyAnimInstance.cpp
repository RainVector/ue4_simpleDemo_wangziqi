// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"
#include "Misc.h"



FRotator UMyAnimInstance::ChangeThumb1()  const {
	
	FRotator ret=FRotator(0.,0.,0.);
	ret = caliThumb1(angleGraphics);

	return ret;
}

FRotator UMyAnimInstance::ChangeThumb3()  const {

	
	FRotator ret = FRotator(0., 0., 0.);
	ret = caliThumb3(angleGraphics);
	return ret;
}

FRotator UMyAnimInstance::ChangeIndex1()  const {
	
	FRotator ret = FRotator(0., 0., 0.);
	ret = caliIndex1(angleGraphics);
	
	return ret;
}
FRotator UMyAnimInstance::ChangeIndex2()  const {
	
	FRotator ret = FRotator(0., 0., 0.);
	ret = caliIndex2(angleGraphics);
	
	return ret;
}

FRotator UMyAnimInstance::ChangeIndex3()  const {
	
	FRotator ret = FRotator(0., 0., 0.);
	ret = caliIndex3(angleGraphics);
	
	return ret;
}
FRotator UMyAnimInstance::ChangeMiddle1()  const {

	FRotator ret = FRotator(0., 0., 0.);
	ret = caliMiddle1(angleGraphics);

	return ret;
}
FRotator UMyAnimInstance::ChangeMiddle2()  const {

	FRotator ret = FRotator(0., 0., 0.);
	ret = caliMiddle2(angleGraphics);

	return ret;
}

FRotator UMyAnimInstance::ChangeMiddle3()  const {

	FRotator ret = FRotator(0., 0., 0.);
	ret = caliMiddle3(angleGraphics);

	return ret;
}
FRotator UMyAnimInstance::ChangeRing1()  const {

	FRotator ret = FRotator(0., 0., 0.);
	ret = caliRing1(angleGraphics);

	return ret;
}
FRotator UMyAnimInstance::ChangeRing2()  const {

	FRotator ret = FRotator(0., 0., 0.);
	ret = caliRing2(angleGraphics);

	return ret;
}

FRotator UMyAnimInstance::ChangeRing3()  const {

	FRotator ret = FRotator(0., 0., 0.);
	ret = caliRing3(angleGraphics);

	return ret;
}
FRotator UMyAnimInstance::ChangeLittle1()  const {

	FRotator ret = FRotator(0., 0., 0.);
	ret = caliLittle1(angleGraphics);

	return ret;
}
FRotator UMyAnimInstance::ChangeLittle2()  const {

	FRotator ret = FRotator(0., 0., 0.);
	ret = caliLittle2(angleGraphics);

	return ret;
}

FRotator UMyAnimInstance::ChangeLittle3()  const {

	FRotator ret = FRotator(0., 0., 0.);
	ret = caliLittle3(angleGraphics);

	return ret;
}





FRotator caliThumb1(float *angle) {
	FRotator var = FRotator(angle[2], angle[0], 0);
	FRotator ret = FRotator(0., 0., 0.);
	/*ret.Pitch = var.Pitch-20;
	ret.Yaw = var.Yaw*2-30+var.Pitch*0.3;*/
	ret.Pitch = -2*var.Pitch;
	ret.Yaw = -3*var.Yaw+90;
	return ret;
}
FRotator caliThumb3(float *angle) {
	FRotator var = FRotator(0, angle[1], 0);
	FRotator ret = FRotator(0., 0., 0.);
	ret.Yaw = -var.Yaw-20;
	return ret;
}


FRotator caliIndex1(float *angle) {
	FRotator var = FRotator(angle[5], angle[3], 0);
	FRotator ret = FRotator(0., 0., 0.);
	ret.Pitch = var.Pitch-10;
	ret.Yaw = var.Yaw-10;
	return ret;
}
FRotator caliIndex2(float *angle) {
	FRotator var = FRotator(0, angle[4], 0);
	FRotator ret = FRotator(0., 0., 0.);
	ret.Yaw = var.Yaw-25;
	return ret;
}
FRotator caliIndex3(float *angle) {
	FRotator var = FRotator(0, angle[4], 0);
	FRotator ret = FRotator(0., 0., 0.);
	ret.Yaw = var.Yaw*0.4-10;
	return ret;
}



FRotator caliMiddle1(float *angle) {
	FRotator var = FRotator(0, angle[6], 0);
	FRotator ret = FRotator(0., 0., 0.);
	ret.Pitch = var.Pitch;
	ret.Yaw = var.Yaw-10;
	return ret;
}
FRotator caliMiddle2(float *angle) {
	FRotator var = FRotator(0, angle[7], 0);
	FRotator ret = FRotator(0., 0., 0.);
	ret.Yaw = var.Yaw-25;
	return ret;
}
FRotator caliMiddle3(float *angle) {
	FRotator var = FRotator(0, angle[7], 0);
	FRotator ret = FRotator(0., 0., 0.);
	ret.Yaw = var.Yaw*0.4-10 ;
	return ret;
}



FRotator caliRing1(float *angle) {
	FRotator var = FRotator(angle[8], angle[9], 0);
	FRotator ret = FRotator(0., 0., 0.);
	ret.Pitch = var.Pitch;
	ret.Yaw = var.Yaw-10;
	return ret;
}
FRotator caliRing2(float *angle) {
	FRotator var = FRotator(0, angle[10], 0);
	FRotator ret = FRotator(0., 0., 0.);
	ret.Yaw = var.Yaw-25;
	return ret;
}
FRotator caliRing3(float *angle) {
	FRotator var = FRotator(0, angle[10], 0);
	FRotator ret = FRotator(0., 0., 0.);
	ret.Yaw = var.Yaw*0.4-10;
	return ret;
}



FRotator caliLittle1(float *angle) {
	FRotator var = FRotator(angle[11], angle[12], 0);
	FRotator ret = FRotator(0., 0., 0.);
	ret.Pitch = var.Pitch+8;
	ret.Yaw = var.Yaw-10;
	return ret;
}
FRotator caliLittle2(float *angle) {
	FRotator var = FRotator(0, angle[13], 0);
	FRotator ret = FRotator(0., 0., 0.);
	ret.Yaw = var.Yaw-25;
	return ret;
}
FRotator caliLittle3(float *angle) {
	FRotator var = FRotator(0, angle[13], 0);
	FRotator ret = FRotator(0., 0., 0.);
	ret.Yaw = var.Yaw*0.4-10;
	return ret;
}