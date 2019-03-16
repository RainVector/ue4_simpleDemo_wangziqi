// Fill out your copyright notice in the Description page of Project Settings.

#include "HandGameModeBase.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include   <ctime>
#include <iostream>
#include  <string>


#include <conio.h>
#include <string.h>
#include <math.h>
#include <Dense>
#include "MyAnimInstance.h"
#include "HandCharacter.h"
#include "BallPawn.h"

#include "SerialComm.h"
#include "Misc.h"

# define ONE_MILLI_SECOND 1 //����1ms��2sʱ�Ӽ������msΪ��λ ��
# define TWO_SECOND 2000
# define TIMER_ACCURACY 1 //����ʱ�ӷֱ��ʣ���msΪ��λ
SerialComm com;
inline wchar_t* AnsiToUnicode(const char* szStr)
{
	int nLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szStr, -1, NULL, 0);
	if (nLen == 0)
	{
		return NULL;
	}
	wchar_t* pResult = new wchar_t[nLen];
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szStr, -1, pResult, nLen);
	return pResult;
}
static void writeForceData(float *force) {
	char bufferWrite[100] = {};
	sprintf(bufferWrite, "%5.2f   %5.2f   %5.2f   %5.2f   %5.2f\r\n", force[0], force[1], force[2], force[3], force[4]);
	com.WriteData((unsigned char *)bufferWrite, 40);
}

static void readBuffer() {
	unsigned char bufferRead[100] = {};
	int temp2 = com.ReadData(bufferRead, 100);
	WCHAR *buffer = AnsiToUnicode((const char *)bufferRead);
	OutputDebugString(buffer);

}

void PASCAL OneMilliSecondProc(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2)
{
	

	static clock_t start, end;
	end = std::clock();
	WCHAR buffer[100];
	double time = (double)(end - start) / CLOCKS_PER_SEC;


	swprintf(buffer, L"%f", time);
	OutputDebugString(buffer);
	start = end;



	OpenHi5Glove();
	com.BlindCommPort(4);
	com.Open();

	while (1) {
		//GetHi5GloveData();
		CalHandOrient(angleHaptics);
		int result_CD = CollisionDetection();
		GraphicsRendering(result_CD);
		float *force= ForceRendering();
		writeForceData(force);
		readBuffer();

		Sleep(10);

	}
	
	CloseHi5Glove();
}

AHandGameModeBase::AHandGameModeBase()
{
	// set default pawn class to our Blueprinted character
	

	UINT wTimerRes_1ms;//����ʱ����
	UINT wAccuracy = 1; //����ֱ���
	UINT TimerID_1ms; //���嶨ʱ�����
	wTimerRes_1ms = 1000;
	if ((TimerID_1ms = timeSetEvent(wTimerRes_1ms, wAccuracy, (LPTIMECALLBACK)OneMilliSecondProc, // �ص�����
		(DWORD)(1), // �û����͵��ص����������ݣ�
		TIME_ONESHOT)) == 0)//���ڵ��ö�ʱ������
	{
		printf("start!!!!!!!!!!!\n");
		printf("start!!!!!!!!!!!\n");
		printf("start!!!!!!!!!!!\n");
	}
	else
	{
		printf("end!!!!!!!!!!!\n");
		printf("end!!!!!!!!!!!\n");
		printf("end!!!!!!!!!!!\n");
		printf("end!!!!!!!!!!!\n");
	}
	
}




