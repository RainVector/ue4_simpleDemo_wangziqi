#include "Misc.h"
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
#include <Eigen/Dense>
#include "MyAnimInstance.h"
#include "HandCharacter.h"
#include "BallPawn.h"
#include "CubePawn.h"
#include "HandCharacter.h"
#include "WISEGLOVE.H"

#include <iostream>
#include <Windows.h>
#include <thread>
#include <vector>

#include "HI5Glove/HI5Glove_C.h"
using namespace HI5Device;

#include "devHtcVive/devHtcVive_C_API.h"
using namespace ViveSystem;

using namespace Eigen;

#pragma comment(lib,"C:/Users/ZYK/Documents/Unreal Projects/Hand_wangziqi/Source/ThirdParty/devHtcVive/devHtcVive.lib")
#pragma comment(lib,"C:/Users/ZYK/Documents/Unreal Projects/Hand_wangziqi/Source/ThirdParty/Hi5Glove/Hi5Glove.lib")

WiseGlove *g_pGlove;
const float handRadius = 1.2;
double g_distance = 0.;
//const float handScale = 10;
//计算点到空间直线的垂足在线段上的比例，其中直线方程为（x-x1）/X = （y-y1）/Y = （z-z1）/Z，法向量（X,Y,Z），点(x0, y0, z0)
double FootPointPtoL(double x1, double y1, double z1,
	double X, double Y, double Z,
	double x0, double y0, double z0)
{
	double temp1 = (x0 - x1) * X;
	double temp2 = (y0 - y1) * Y;
	double temp3 = (z0 - z1) * Z;
	double temp4 = temp1 + temp2 + temp3;
	double temp5 = X * X + Y * Y + Z * Z;
	double scale = temp4 / temp5;
	return scale;
}
//计算点到空间直线距离的平方，其中直线方程为（x-x1）/X = （y-y1）/Y = （z-z1）/Z，法向量（X,Y,Z），点(x0, y0, z0)
double Distance2PtoL(double x1, double y1, double z1,
	double X, double Y, double Z,
	double x0, double y0, double z0)
{
	double temp1 = (y0 - y1) * Z - Y * (z0 - z1);
	temp1 = temp1 * temp1;
	double temp2 = (z0 - z1) * X - Z * (x0 - x1);
	temp2 = temp2 * temp2;
	double temp3 = (x0 - x1) * Y - X * (y0 - y1);
	temp3 = temp3 * temp3;
	double temp4 = temp1 + temp2 + temp3;
	double temp5 = X*X + Y*Y + Z*Z;
	double d;
	return d = temp4 / temp5;
}

//add by xixi 2018.1.31
double Distance2PtoC(double x1, double y1, double z1, double x2, double y2, double z2, double x0, double y0, double z0) {
	double temp1 = pow((x1 - x0), 2) + pow((y1 - y0), 2) + pow((z1 - z0), 2);
	double temp2 = pow((x2 - x0), 2) + pow((y2 - y0), 2) + pow((z2 - z0), 2);
	double res = temp1 < temp2 ? temp1 : temp2;
	return res;
}
int objCdFlag[5] = { 0 };
bool IntersectHand(FVector *finger, InfoBall ball, InfoCube cube, int fingerID)
{
	if (handRadius <= 0 || ball.radius <= 0)
	{
		return FALSE;
	}
	double tempR = handRadius + ball.radius;
	double x1 = finger[2].X;
	double y1 = finger[2].Y;
	double z1 = finger[2].Z;
	double X = finger[2].X - finger[3].X;
	double Y = finger[2].Y - finger[3].Y;
	double Z = finger[2].Z - finger[3].Z;
	double x2 = finger[3].X;
	double y2 = finger[3].Y;
	double z2 = finger[3].Z;
	double x0, y0, z0;

	//判断物体球是否在圆柱轴线段之外，物体球半径没有考虑
	x0 = ball.x;
	y0 = ball.y;
	z0 = ball.z;
	double scale_start;
	scale_start = FootPointPtoL(x1, y1, z1, X, Y, Z, x0, y0, z0);
	//tempscale = scale_start;



	// 离散碰撞检测
	double Dist_2 = Distance2PtoL(x1, y1, z1, X, Y, Z, x0, y0, z0);
	double Dist_PC = Distance2PtoC(x1, y1, z1, x2, y2, z2, x0, y0, z0);
	bool cdFlag = FALSE;
	g_distance = sqrt(Dist_2) - tempR;
	if (g_distance < 0)
	{

		if (scale_start > 1 || scale_start < 1.0e-3)	//如果点不在圆柱线段内
		{
			if (Dist_PC <= pow(tempR, 2))
			{
				cdFlag = TRUE;
			}
			else
				cdFlag = FALSE;
		}
		else
			cdFlag = TRUE;
	}
	else
		cdFlag = FALSE;

	double height1 = cube.z - cube.halfHeight;
	double height2 = cube.z + cube.halfHeight;
	double width1 = cube.y - cube.halfHeight;
	if (fingerID == 0) {
		if ((y2 - width1) > 0) {
			cdFlag = TRUE;
			objCdFlag[fingerID] = 1;
		}
	}
	else{
		if ((z1 - height1)*(z2 - height1) < 0 || (z2 - height2) < 0) {
			cdFlag = TRUE;
			objCdFlag[fingerID] = 1;
		}
	}
	

	return cdFlag;
}
Matrix4f transMatrixMakerXYZ(float alpha, float beta, float gamma, float X, float Y, float Z) {
	Matrix4f ret;
	alpha = alpha / 180 * PI;
	beta = beta / 180 * PI;
	gamma = gamma / 180 * PI;



	/*ret << cos(beta)*cos(gamma), -cos(beta)*sin(gamma), sin(beta), X,
		cos(alpha)*sin(gamma) + cos(gamma)*sin(alpha)*sin(beta), cos(alpha)*cos(gamma) - sin(alpha)*sin(beta)*sin(gamma), -cos(beta)*sin(alpha), Y, 
		sin(alpha)*sin(gamma) - cos(alpha)*cos(gamma)*sin(beta), cos(gamma)*sin(alpha) + cos(alpha)*sin(beta)*sin(gamma), cos(alpha)*cos(beta), Z,
		0, 0, 0, 1;*/
	/*ret << cos(beta)*cos(gamma), cos(beta)*sin(gamma), -sin(beta), X,
		cos(gamma)*sin(alpha)*sin(beta) - cos(alpha)*sin(gamma), cos(alpha)*cos(gamma) + sin(alpha)*sin(beta)*sin(gamma), cos(beta)*sin(alpha), Y,
		sin(alpha)*sin(gamma) + cos(alpha)*cos(gamma)*sin(beta), cos(alpha)*sin(beta)*sin(gamma) - cos(gamma)*sin(alpha), cos(alpha)*cos(beta), Z,
		0, 0, 0, 1;*/
	ret << cos(beta)*cos(gamma), cos(alpha)*sin(gamma) + cos(gamma)*sin(alpha)*sin(beta), sin(alpha)*sin(gamma) - cos(alpha)*cos(gamma)*sin(beta), X,
		-cos(beta)*sin(gamma), cos(alpha)*cos(gamma) - sin(alpha)*sin(beta)*sin(gamma), cos(gamma)*sin(alpha) + cos(alpha)*sin(beta)*sin(gamma), Y,
		sin(beta), -cos(beta)*sin(alpha), cos(alpha)*cos(beta), Z,
		0, 0, 0, 1;

	

	return ret;
}


Matrix4f transMatrixMakerZYX(float alpha, float beta, float gamma, float X, float Y, float Z) {
	Matrix4f ret;
	alpha = alpha / 180 * PI;
	beta = beta / 180 * PI;
	gamma = gamma / 180 * PI;

	

	/*ret << cos(beta)*cos(gamma), -cos(beta)*sin(gamma), -sin(beta), X,
			cos(alpha)*sin(gamma) - cos(gamma)*sin(alpha)*sin(beta), cos(alpha)*cos(gamma) + sin(alpha)*sin(beta)*sin(gamma), -cos(beta)*sin(alpha), Y,
				sin(alpha)*sin(gamma) + cos(alpha)*cos(gamma)*sin(beta), cos(gamma)*sin(alpha) - cos(alpha)*sin(beta)*sin(gamma), cos(alpha)*cos(beta), Z,
				0, 0, 0, 1;*/
		/*ret << cos(beta)*cos(gamma), -cos(beta)*sin(gamma), sin(beta), X,
			cos(alpha)*sin(gamma) + cos(gamma)*sin(alpha)*sin(beta), cos(alpha)*cos(gamma) - sin(alpha)*sin(beta)*sin(gamma), -cos(beta)*sin(alpha), Y, 
			sin(alpha)*sin(gamma) - cos(alpha)*cos(gamma)*sin(beta), cos(gamma)*sin(alpha) + cos(alpha)*sin(beta)*sin(gamma), cos(alpha)*cos(beta), Z,
			0, 0, 0, 1;*/
	/*ret << cos(beta)*cos(gamma), cos(gamma)*sin(alpha)*sin(beta) - cos(alpha)*sin(gamma), sin(alpha)*sin(gamma) + cos(alpha)*cos(gamma)*sin(beta), X,
	cos(beta)*sin(gamma), cos(alpha)*cos(gamma) + sin(alpha)*sin(beta)*sin(gamma), cos(alpha)*sin(beta)*sin(gamma) - cos(gamma)*sin(alpha), Y,
	-sin(beta), cos(beta)*sin(alpha), cos(alpha)*cos(beta), Z,
	0, 0, 0, 1;*/

		/*ret << cos(beta)*cos(gamma), -cos(alpha)*sin(gamma) - cos(gamma)*sin(alpha)*sin(beta), sin(alpha)*sin(gamma) - cos(alpha)*cos(gamma)*sin(beta), X,
			cos(beta)*sin(gamma), cos(alpha)*cos(gamma) - sin(alpha)*sin(beta)*sin(gamma), -cos(gamma)*sin(alpha) - cos(alpha)*sin(beta)*sin(gamma), Y,
			sin(beta), cos(beta)*sin(alpha), cos(alpha)*cos(beta), Z,
			0, 0, 0, 1;*/
	ret << cos(beta)*cos(gamma), cos(gamma)*sin(alpha)*sin(beta) - cos(alpha)*sin(gamma), -sin(alpha)*sin(gamma) - cos(alpha)*cos(gamma)*sin(beta), X,
		cos(beta)*sin(gamma), cos(alpha)*cos(gamma) + sin(alpha)*sin(beta)*sin(gamma), cos(gamma)*sin(alpha) - cos(alpha)*sin(beta)*sin(gamma), Y,
		sin(beta), -cos(beta)*sin(alpha), cos(alpha)*cos(beta), Z,
		0, 0, 0, 1;

	return ret;
}



#define REDUCED_OUTPUT_DATA_FREQ    3

bool bReading = false;
std::thread *hi5DataReaderThread = nullptr;
std::thread *hi5FetchStatusThread = nullptr;
std::thread *viveDataReaderThread = nullptr;

void __stdcall fnDongleStateChanged(void *userData, const DongleIdentity *hid, DongleEvent action)
{
	const char *strAct = (action == DE_Insert ? "inserted" : "removed");
	std::cout << "### Dongle(SN:" << hid->SerialNumber << ") " << strAct << std::endl;
}

void __stdcall fnGloveStateChanged(void *userData, GloveMod glove, GloveEvent event)
{
	const char *strGlove = (glove == GM_LeftGlove ? "Left glove " : "Right glove ");
	char *strAct = nullptr;
	switch (event)
	{
	case GE_LowPower: // Low power
		strAct = "Low power";
		break;
	case GE_NormalPower: // Normal power
		strAct = "Normal power";
		break;
	case GE_FullPower: // Full power
		strAct = "Full power";
		break;
	case GE_NotMagneticed: // Not magneticed
		strAct = "Not magneticed";
		break;
	case GE_Magneticed: // Magneticed
		strAct = "Magneticed";
		break;
	case GE_RadioFrequencyChanged: // Radio frequency changed
		strAct = "Radio frequency changed";
		break;
	case GE_Unknown:
	default:
		strAct = "Unknown action";
		break;
	}
	std::cout << "### " << strGlove << strAct << std::endl;
}

void calibration(CalibrationPose pos, int wait /*ms*/)
{
	// calibration
	startCalibration(pos);

	const int sleepms = 50;

	// get percent
	int percent = 0;
	int waitCount = 0;
	int waitTotal = wait / sleepms;
	while (percent != 100 && waitCount < waitTotal)
	{
		CalibrationPercent caliP = getCalibratingPercent(pos);
		if (caliP.percent != percent)
		{
			std::cout << "Calibration: " << caliP.percent << "%" << std::endl;
			percent = caliP.percent;
		}
		if (percent == 100)
		{
			std::cout << "Done" << std::endl;
			break;
		}
		if (!bReading)
		{
			std::cout << "Calibration process stoped because reading thread exited" << std::endl;
			break;
		}
		Sleep(sleepms);
		waitCount++;
	}
	if (percent != 100)
	{
		std::cout << "Time out" << std::endl;
	}
}

void tFetchStatusThead()
{
	std::cout << std::endl;
	std::cout << "Get dongle SN:" << getDongleSN() << std::endl;

	std::cout << std::endl;
	std::cout << "getDongleRunningMode: " << std::endl;
	std::cout << " dongle mod: " << getDongleRunningMode() << std::endl;

	std::cout << std::endl;
	std::cout << "getDongleFirmwareVersion: " << std::endl;
	DongleFirmwareVersion dongleVer;
	memset(&dongleVer, 0, sizeof(dongleVer));
	getDongleFirmwareVersion(&dongleVer);
	std::cout << " appVer=" << dongleVer.appVer.major << "."
		<< dongleVer.appVer.minor << "." << dongleVer.appVer.rev << "."
		<< dongleVer.appVer.build << std::endl;
	std::cout << " booter=" << dongleVer.bootVer.major << "."
		<< dongleVer.bootVer.minor << "." << dongleVer.bootVer.rev << "."
		<< dongleVer.bootVer.build << std::endl;

	std::cout << std::endl;
	std::cout << "getGloveFirmwareVersion: " << std::endl;
	GloveFirmwareVersion gloveVerL;
	GloveFirmwareVersion gloveVerR;
	memset(&gloveVerL, 0, sizeof(gloveVerL));
	memset(&gloveVerR, 0, sizeof(gloveVerR));
	getGloveFirmwareVersion(&gloveVerL, &gloveVerR);
	std::cout << "Left glove: " << std::endl;
	std::cout << " booter=" << gloveVerL.bootVer.major << "."
		<< gloveVerL.bootVer.minor << "." << gloveVerL.bootVer.rev << "."
		<< gloveVerL.bootVer.build << std::endl;
	std::cout << " appM0Ver=" << gloveVerL.appM0Ver.major << "."
		<< gloveVerL.appM0Ver.minor << "." << gloveVerL.appM0Ver.rev
		<< "." << gloveVerL.appM0Ver.build << std::endl;
	std::cout << " appM4Ver=" << gloveVerL.appM4Ver.major << "."
		<< gloveVerL.appM4Ver.minor << "." << gloveVerL.appM4Ver.rev
		<< "." << gloveVerL.appM4Ver.build << std::endl;
	std::cout << "Right glove: " << std::endl;
	std::cout << " booter=" << gloveVerR.bootVer.major << "."
		<< gloveVerR.bootVer.minor << "." << gloveVerR.bootVer.rev << "."
		<< gloveVerR.bootVer.build << std::endl;
	std::cout << " appM0Ver=" << gloveVerR.appM0Ver.major << "."
		<< gloveVerR.appM0Ver.minor << "." << gloveVerR.appM0Ver.rev
		<< "." << gloveVerR.appM0Ver.build << std::endl;
	std::cout << " appM4Ver=" << gloveVerR.appM4Ver.major << "."
		<< gloveVerR.appM4Ver.minor << "." << gloveVerR.appM4Ver.rev
		<< "." << gloveVerR.appM4Ver.build << std::endl;

	std::cout << std::endl;
	std::cout << "getGlovesPowerLevel: " << std::endl;
	int l = 0;
	int r = 0;
	getGlovesPowerLevel(&l, &r);
	std::cout << " level: left=" << l << " right=" << r << std::endl;


	std::cout << std::endl;
	std::cout << "getCurrentRadioFrequency: " << std::endl;
	std::cout << " freq: " << getCurrentRadioFrequency() << std::endl;

	std::cout << std::endl;
	std::cout << "getDongleRadioFrequencyTable: " << std::endl;
	unsigned int freqTab[32];
	memset(freqTab, 0, sizeof(freqTab));
	int tabsize = getDongleRadioFrequencyTable(freqTab);
	std::cout << " tab size: " << tabsize << std::endl;
	std::cout << " freq tab: " << std::endl;
	for (int i = 0; i < tabsize; i++)
	{
		std::cout << " freq: " << freqTab[i] << std::endl;
	}

	if (tabsize)
	{
		int freq = freqTab[2];
		std::cout << std::endl;
		std::cout << "setDongleRadioFrequency: (Lock freq to " << freq << ")" << std::endl;
		std::cout << (setDongleRadioFrequency(freq) ? " Successful" : " Failed") << std::endl;
	}

	// Hand thickness settings
	std::cout << std::endl;
	std::cout << "getHandThickness: " << std::endl;
	float handThickness = getHandThickness();
	std::cout << "  hand thickness: " << handThickness << std::endl;

	std::cout << "setHandThickness: " << std::endl;
	handThickness = 0.06666;
	setHandThickness(handThickness);
	std::cout << "  set hand thickness to: " << handThickness << std::endl;
	std::cout << "getHandThickness: " << std::endl;
	handThickness = getHandThickness();
	std::cout << "  hand thickness: " << handThickness << std::endl;


	// Wrist postition settings
	std::cout << std::endl;
	std::cout << "getWristPositionInTrackerFrame: " << std::endl;
	float leftTrackerOffset[3];
	float rightTrackerOffset[3];
	getWristPositionInTrackerFrame(leftTrackerOffset, rightTrackerOffset);
	std::cout << "  Wrist position: l=(" << leftTrackerOffset[0] << "," << leftTrackerOffset[1] << "," << leftTrackerOffset[2] << ")" << std::endl;
	std::cout << "                  r=(" << rightTrackerOffset[0] << "," << rightTrackerOffset[1] << "," << rightTrackerOffset[2] << ")" << std::endl;

	std::cout << "setWristPositionInTrackerFrame: " << std::endl;
	leftTrackerOffset[0] = 1.0;
	rightTrackerOffset[0] = 1.0;
	setWristPositionInTrackerFrame(leftTrackerOffset, rightTrackerOffset);
	std::cout << "  setWristPositionInTrackerFrame to: l=(" << leftTrackerOffset[0] << "," << leftTrackerOffset[1] << "," << leftTrackerOffset[2] << ")" << std::endl;
	std::cout << "                                     r=(" << rightTrackerOffset[0] << "," << rightTrackerOffset[1] << "," << rightTrackerOffset[2] << ")" << std::endl;
	std::cout << "getWristPositionInTrackerFrame: " << std::endl;
	getWristPositionInTrackerFrame(leftTrackerOffset, rightTrackerOffset);
	std::cout << "  Wrist position: l=(" << leftTrackerOffset[0] << "," << leftTrackerOffset[1] << "," << leftTrackerOffset[2] << ")" << std::endl;
	std::cout << "                  r=(" << rightTrackerOffset[0] << "," << rightTrackerOffset[1] << "," << rightTrackerOffset[2] << ")" << std::endl;


	int fetchTimes = 0;
	HI5GloveStatus status = DV_Unknown;
	while (bReading)
	{
		// read status
		status = DV_Unknown;
		readDeviceStatus(&status);
		switch (status) {
		case DV_NoDongle:
			printf("status: DV_NoDongle\n");
			Sleep(500);
			continue;
		case DV_NoGlove:
			printf("status: DV_NoGlove\n");
			Sleep(500);
			continue;
		case DV_LeftGloveAvailable:
			printf("status: DV_LeftGloveAvailable\n");
			break;
		case DV_RightGloveAvailable:
			printf("status: DV_RightGloveAvailable\n");
			break;
		case DV_BothGloveAvailable:
			printf("status: DV_BothGloveAvailable\n");
			break;
		case DV_Unknown:
		case DV_MaxNumb:
		default:
			continue;
		}

		// check radio setting
		std::cout << std::endl;
		std::cout << "getCurrentRadioFrequency: " << std::endl;
		std::cout << " freq: " << getCurrentRadioFrequency() << std::endl;

		fetchTimes++;
		std::cout << "Fetch times: " << fetchTimes << std::endl;

		Sleep(1000); // 1s
	}
}

void fnViveDeviceStatusChanged(int devCount, DeviceEvent sEvent, DeviceEventArg arg)
{
	printf("Paired devices: %d, sEvent: %d, SN: %s, nNewIndex: %d, nOldIndex: %d\n",
		devCount, sEvent, arg.strSN, arg.nNewIndex, arg.nOldIndex);
}

void tViveReadThead()
{
	DeviceStatus errn = DevStatus_OK;
	initViveLib(errn);

	setDeviceStatusChangedHandle(fnViveDeviceStatusChanged);

	TrackedDevicePose dataBuffer[16];

	while (bReading)
	{
		memset(dataBuffer, 0, sizeof(dataBuffer));

		errn = DevStatus_OK;
		readViveData(dataBuffer, errn);
		if (errn != DevStatus_OK)
		{
			Sleep(100);
			continue;
		}

		for (size_t i = 0; i < MAX_DEVICE_COUNT; i++)
		{
			TrackedDevicePose *d = &dataBuffer[i];
			if (d->bPoseValid)
			{
				// Optical sensor type
				OpticalSensorType stype = OST_Unknown;
				if (d->eDataType == DT_Controller)
				{
					stype = OST_HTC_VIVE_Controller;
				}
				else if (d->eDataType == DT_Tracker)
				{
					stype = OST_HTC_VIVE_Tracker;
				}

				// input into sdk
				if (stype != OST_Unknown)
				{
					HI5Device::pushOpticalSensorData(d->strSN, stype, d->fPosition, d->fRotation);
				}
			}
		}
	}

	releaseViveLib();
}
GloveBVHData bvhData; // left and right glove data
float angleHaptics[14];
void tDeviceReadThead(void *param)
{
	std::cout << std::endl;
	std::cout << "Set reduced output data freq to 3" << std::endl;
	setReducedOutputDataFreq(REDUCED_OUTPUT_DATA_FREQ);

	std::cout << std::endl;
	std::cout << "enableVibrator: " << std::endl;
	enableLeftGloveVibrator(100);
	Sleep(50);
	enableRightGloveVibrator(100);


	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "            Start calibration                    " << std::endl;
	std::cout << "*******************************************************" << std::endl;

	char calFile[100];
	sprintf(calFile, "%s", "C:/Users/ZYK/Documents/Unreal Projects/Hand_wangziqi/Source/ThirdParty/Hi5Glove/CalibrationData4");
	//sprintf(calFile, "%s", "E:/CalibrationData4");
	std::cout << std::endl;
	std::cout << "Loading calibration file: " << calFile;
	bool calibrated = !(loadCalibrationData(calFile)==0);
	std::cout << (calibrated ? "successful" : "failed") << std::endl;
	if (!calibrated)
	{
		std::cout << std::endl;
		std::cout << "1. calibrationPrepare" << std::endl;
		calibrationPrepare();

		std::cout << std::endl;
		std::cout << "2. startCalibration: GCP_APose" << std::endl;
		calibration(GCP_APose, 5000);

		std::cout << std::endl;
		std::cout << "3. startCalibration: GCP_TPose" << std::endl;
		calibration(GCP_TPose, 5000);

		std::cout << std::endl;
		std::cout << "4. startCalibration: GCP_PPose" << std::endl;
		calibration(GCP_PPose, 5000);

		std::cout << std::endl;
		std::cout << "5. startCalibration: GCP_BPose" << std::endl;
		calibration(GCP_BPose, 10000);

		std::cout << std::endl;
		std::cout << "6. startCalibration: GCP_CPose" << std::endl;
		calibration(GCP_CPose, 20000);

		// save calc result
		std::cout << "Saving calibration file: " << calFile;
		calibrated = !(saveCalibrationData(calFile)==0);
		std::cout << (calibrated ? "successful" : "failed") << std::endl;
	}

	int len = 0;
	char leftBoundSN[64];
	leftBoundSN[0] = 0;
	OpticalSensorType leftOptiSensorType = OST_Unknown;
	len = getOptiSensorBindState(GM_LeftGlove, leftBoundSN, sizeof(leftBoundSN), &leftOptiSensorType);
	if (len > 0) {
		setOptiSensorBindState(GM_LeftGlove, leftBoundSN, leftOptiSensorType);
		std::cout << "   getOptiSensorBindState: Left hand: " << leftBoundSN
			<< std::endl;
		std::cout << "   setOptiSensorBindState: Left hand: " << leftBoundSN
			<< std::endl;
	}
	char rightBoundSN[64];
	rightBoundSN[0] = 0;
	OpticalSensorType rightOptiSensorType = OST_Unknown;
	len = getOptiSensorBindState(GM_RightGlove, rightBoundSN, sizeof(rightBoundSN), &rightOptiSensorType);
	if (len > 0) {
		setOptiSensorBindState(GM_RightGlove, rightBoundSN, rightOptiSensorType);
		std::cout << "   getOptiSensorBindState: Right hand: " << rightBoundSN
			<< std::endl;
		std::cout << "   setOptiSensorBindState: Right hand: " << rightBoundSN
			<< std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "               Reading data                            "
		<< std::endl;
	std::cout << "*******************************************************"
		<< std::endl;
	std::cout << std::endl;

	HI5GloveStatus status;

	int s_count = 0;
	
	while (bReading)
	{
		// read status
		status = DV_Unknown;
		readDeviceStatus(&status);
		if (status != DV_LeftGloveAvailable && status != DV_RightGloveAvailable && status != DV_BothGloveAvailable)
		{
			Sleep(500);
		}

		// read data
		memset(&bvhData, 0, sizeof(GloveBVHData));
		readBVHData(&bvhData);
		if (!bvhData.bUpdate) {
			Sleep(1);
			continue;
		}
		//dataFetch zyk
		float angle[14] = { bvhData.data[6 + 0 * 4 * 6 + 9], bvhData.data[6 + 0 * 4 * 6 + 21], bvhData.data[6 + 0 * 4 * 6 + 11], \
			bvhData.data[6 + 1 * 4 * 6 + 11], bvhData.data[6 + 1 * 4 * 6 + 17], bvhData.data[6 + 1 * 4 * 6 + 9],\
			bvhData.data[6 + 2 * 4 * 6 + 11], bvhData.data[6 + 2 * 4 * 6 + 17], bvhData.data[6 + 2 * 4 * 6 + 9],\
			bvhData.data[6 + 3 * 4 * 6 + 11], bvhData.data[6 + 3 * 4 * 6 + 17], bvhData.data[6 + 3 * 4 * 6 + 9],\
			bvhData.data[6 + 4 * 4 * 6 + 11], bvhData.data[6 + 4 * 4 * 6 + 17]
		};

		memcpy(angleHaptics, angle, sizeof(angle));
		// print one frame per second
		if (s_count++ % (DATA_FREQUENCY / REDUCED_OUTPUT_DATA_FREQ) == 0)
		{
			printf("frameIndex: %d, Glove: %s, whith displacement: %s:\n", bvhData.frameIndex, (bvhData.glove == HI5Device::GM_LeftGlove ? "LeftGlove" : "RightGlove"), (bvhData.bWithDisp != 0 ? "Yes" : "No"));
			int idx = 0;
			while (idx < bvhData.dataCount)
			{
				if (bvhData.bWithDisp)
				{
					printf("positon: %0.3f,%0.3f,%0.3f\t", bvhData.data[idx], bvhData.data[idx + 1], bvhData.data[idx + 2]);
					idx += 3;
				}
				printf("rotate: %0.3f,%0.3f,%0.3f\n", bvhData.data[idx], bvhData.data[idx + 1], bvhData.data[idx + 2]);
				idx += 3;
			}
			std::cout << std::endl;
		}
	}
}


//void tInputCtrlThead(int *exitCode) {
//	*exitCode = getchar();
//	while (*exitCode)
//	{
//		break;
//	}
//}

void OpenHi5Glove() {
	std::cout << "*******************************************************" << std::endl;
	std::cout << "*          HI5Glove SDK libray tests                  *" << std::endl;
	std::cout << "*******************************************************" << std::endl;
	std::cout << std::endl;

	std::cout << "Set event handles" << std::endl;
	setDongleStateChangedHandle(nullptr, fnDongleStateChanged);
	setGloveStateChangedHandle(nullptr, fnGloveStateChanged);

	std::cout << "Start dongle" << std::endl;
	hi5DongleStart();

	int exitCode = 0;
	/*std::thread exitCtrl(tInputCtrlThead, &exitCode);*/
	//while (exitCode == 0) {
	while (exitCode == 0) {
	if (isDongleAvailable()) {
			bReading = true;
			if (hi5DataReaderThread == nullptr) {
				hi5DataReaderThread = new std::thread(tDeviceReadThead, nullptr);
			}
			if (hi5FetchStatusThread == nullptr) {
				hi5FetchStatusThread = new std::thread(tFetchStatusThead);
			}
			if (viveDataReaderThread == nullptr) {
				viveDataReaderThread = new std::thread(tViveReadThead);
			}
			exitCode = 1;
		}
		else {
			bReading = false;
			if (hi5DataReaderThread) {
				hi5DataReaderThread->join();
				delete hi5DataReaderThread;
				hi5DataReaderThread = nullptr;
			}
			if (hi5FetchStatusThread) {
				hi5FetchStatusThread->join();
				delete hi5FetchStatusThread;
				hi5FetchStatusThread = nullptr;
			}
			if (viveDataReaderThread) {
				viveDataReaderThread->join();
				delete viveDataReaderThread;
				viveDataReaderThread = nullptr;
			}
		}

		Sleep(200);
	}
}






void GetHi5GloveData() {
	
}



void CalHandOrient(float *angle) {
	Vector4f thumbLoc[4];
	thumbLoc[3] << 3., 0., 0., 1.;//估计末端指节长度为3.
	thumbLoc[2] << 6.1, 0., 0., 1.;
	thumbLoc[1] << 6.6, 0., 0., 1.;
	thumbLoc[0] << 2.734, 1.383, -2.649, 1.;


	Matrix4f T_3to2_thumb = transMatrixMakerZYX(0., 0., 19.452, 6.168, 0., 0.);
	Matrix4f T_2to1_thumb = transMatrixMakerZYX(7.498, 1.250, 22.977, 6.648, 0., 0.);
	//Matrix4f T_2to1_thumb = transMatrixMakerZYX(0., 0., 0., 4.73, 4.57, 0.);
	Matrix4f T_1toH_thumb = transMatrixMakerZYX(-103.668, -34.847, 23.054, 2.734, 1.383, -2.649);
	Matrix4f T_HtoL3 = transMatrixMakerZYX(0., 0., 0., 9.965, 0., 0.);
	Matrix4f T_L3toL2 = transMatrixMakerZYX(0., 0.209, 0.0, 13.171, 0., 0.);
	Matrix4f T_L2toL1 = transMatrixMakerZYX(0., 0., 0., 15.346, 0., 0.);
	Matrix4f T_L1toU = transMatrixMakerZYX(0., -8.629, 0., 44.25, 0., 0.);
	Matrix4f T_UtoWorld = transMatrixMakerZYX(-179.999, 87.329, -179.999, -25., 0., 0.);

	FRotator rotThumb1 = caliThumb1(angle);
	FRotator rotThumb3 = caliThumb3(angle);

	Matrix4f T_rotThumb1 = transMatrixMakerZYX(rotThumb1.Roll, rotThumb1.Pitch, rotThumb1.Yaw, 0., 0., 0.);
	Matrix4f T_rotThumb3 = transMatrixMakerZYX(rotThumb3.Roll, rotThumb3.Pitch, rotThumb3.Yaw, 0., 0., 0.);

	thumbLoc[2] = T_UtoWorld*T_L1toU*T_L2toL1*T_L3toL2*T_HtoL3*T_1toH_thumb*T_rotThumb1*T_2to1_thumb*thumbLoc[2];
	thumbLocation[2] = FVector(thumbLoc[2](0, 0), thumbLoc[2](1, 0), thumbLoc[2](2, 0));
	thumbLocation[2] = skelToWorld.RotateVector(thumbLocation[2]);

	thumbLoc[3] = T_UtoWorld*T_L1toU*T_L2toL1*T_L3toL2*T_HtoL3*T_1toH_thumb*T_rotThumb1*T_2to1_thumb*T_3to2_thumb*T_rotThumb3*thumbLoc[3];
	thumbLocation[3] = FVector(thumbLoc[3](0, 0), thumbLoc[3](1, 0), thumbLoc[3](2, 0));
	thumbLocation[3] = skelToWorld.RotateVector(thumbLocation[3]);

	/*WCHAR buffer[300];
	swprintf(buffer, L"The thumb's fingertip is at (%f, %f, %f).\r\n The thumb3 is at (%f, %f, %f).\r\n The distance is %f.\r\n", thumbLocation[3].X, thumbLocation[3].Y, thumbLocation[3].Z, thumbLocation[2].X, thumbLocation[2].Y, thumbLocation[2].Z, g_distance);
	OutputDebugString(buffer);*/



	Vector4f indexLoc[4];
	
	indexLoc[3] << 3., 0., 0., 1.;//估计末端指节长度为3.
	indexLoc[2] << 3.4, 0., 0., 1.;

	Matrix4f T_3to2_index = transMatrixMakerZYX(0., 0., 11.998, 3.414, 0., 0.);
	Matrix4f T_2to1_index = transMatrixMakerZYX(-0.869, -0.376, 37.619, 5.578, 0., 0.);
	Matrix4f T_1toH_index = transMatrixMakerZYX(-1.725, 4.505, 19.378, 14.395, 0., -4.216);

	FRotator rotIndex1 = caliIndex1(angle);
	FRotator rotIndex2 = caliIndex2(angle);
	FRotator rotIndex3 = caliIndex3(angle);

	Matrix4f T_rotIndex1 = transMatrixMakerZYX(rotIndex1.Roll, rotIndex1.Pitch, rotIndex1.Yaw, 0., 0., 0.);
	Matrix4f T_rotIndex2 = transMatrixMakerZYX(rotIndex2.Roll, rotIndex2.Pitch, rotIndex2.Yaw, 0., 0., 0.);
	Matrix4f T_rotIndex3 = transMatrixMakerZYX(rotIndex3.Roll, rotIndex3.Pitch, rotIndex3.Yaw, 0., 0., 0.);

	indexLoc[2] = T_UtoWorld*T_L1toU*T_L2toL1*T_L3toL2*T_HtoL3*T_1toH_index*T_rotIndex1*T_2to1_index*T_rotIndex2*indexLoc[2];
	
	indexLocation[2] = FVector(indexLoc[2](0, 0), indexLoc[2](1, 0), indexLoc[2](2, 0));
	indexLocation[2] = skelToWorld.RotateVector(indexLocation[2]);

	indexLoc[3] = T_UtoWorld*T_L1toU*T_L2toL1*T_L3toL2*T_HtoL3*T_1toH_index*T_rotIndex1*T_2to1_index*T_rotIndex2*T_3to2_index*T_rotIndex3*indexLoc[3];
	indexLocation[3] = FVector(indexLoc[3](0, 0), indexLoc[3](1, 0), indexLoc[3](2, 0));
	indexLocation[3] = skelToWorld.RotateVector(indexLocation[3]);

	/*WCHAR buffer[300];
	swprintf(buffer, L"The fingertip is at (%f, %f, %f).\r\n The index3 is at (%f, %f, %f).\r\n The distance is %f.\r\n", indexLocation[3].X, indexLocation[3].Y, indexLocation[3].Z, indexLocation[2].X, indexLocation[2].Y, indexLocation[2].Z, g_distance);
	OutputDebugString(buffer);*/

	Vector4f middleLoc[4];

	middleLoc[3] << 3., 0., 0., 1.;//估计末端指节长度为3.
	middleLoc[2] << 3.4, 0., 0., 1.;

	Matrix4f T_3to2_middle = transMatrixMakerZYX(-0.618, 2.167, 28.925, 3.66, 0., 0.);
	Matrix4f T_2to1_middle = transMatrixMakerZYX(2.648, -1.937, 36.3, 6.914, 0., 0.);
	Matrix4f T_1toH_middle = transMatrixMakerZYX(3.64, 6.927, 27.912, 13.855, -0.393, -0.795);

	FRotator rotMiddle1 = caliMiddle1(angle);
	FRotator rotMiddle2 = caliMiddle2(angle);
	FRotator rotMiddle3 = caliMiddle3(angle);

	Matrix4f T_rotMiddle1 = transMatrixMakerZYX(rotMiddle1.Roll, rotMiddle1.Pitch, rotMiddle1.Yaw, 0., 0., 0.);
	Matrix4f T_rotMiddle2 = transMatrixMakerZYX(rotMiddle2.Roll, rotMiddle2.Pitch, rotMiddle2.Yaw, 0., 0., 0.);
	Matrix4f T_rotMiddle3 = transMatrixMakerZYX(rotMiddle3.Roll, rotMiddle3.Pitch, rotMiddle3.Yaw, 0., 0., 0.);

	middleLoc[2] = T_UtoWorld*T_L1toU*T_L2toL1*T_L3toL2*T_HtoL3*T_1toH_middle*T_rotMiddle1*T_2to1_middle*T_rotMiddle2*middleLoc[2];

	middleLocation[2] = FVector(middleLoc[2](0, 0), middleLoc[2](1, 0), middleLoc[2](2, 0));
	middleLocation[2] = skelToWorld.RotateVector(middleLocation[2]);

	middleLoc[3] = T_UtoWorld*T_L1toU*T_L2toL1*T_L3toL2*T_HtoL3*T_1toH_middle*T_rotMiddle1*T_2to1_middle*T_rotMiddle2*T_3to2_middle*T_rotMiddle3*middleLoc[3];
	middleLocation[3] = FVector(middleLoc[3](0, 0), middleLoc[3](1, 0), middleLoc[3](2, 0));
	middleLocation[3] = skelToWorld.RotateVector(middleLocation[3]);

	/*WCHAR buffer[300];
	swprintf(buffer, L"The fingertip is at (%f, %f, %f).\r\n The middle3 is at (%f, %f, %f).\r\n The distance is %f.\r\n", middleLocation[3].X, middleLocation[3].Y, middleLocation[3].Z, middleLocation[2].X, middleLocation[2].Y, middleLocation[2].Z, g_distance);
	OutputDebugString(buffer);*/

	Vector4f ringLoc[4];

	ringLoc[3] << 3., 0., 0., 1.;//估计末端指节长度为3.
	ringLoc[2] << 3.4, 0., 0., 1.;

	Matrix4f T_3to2_ring = transMatrixMakerZYX(-2.954, -0.023, 32.818, 3.735, 0., 0.);
	Matrix4f T_2to1_ring = transMatrixMakerZYX(4.088, -0.368, 34.830, 6.011, 0., 0.);
	Matrix4f T_1toH_ring = transMatrixMakerZYX(9.629, 5.917, 31.195, 13.236, -0.224, 2.867);

	FRotator rotRing1 = caliRing1(angle);
	FRotator rotRing2 = caliRing2(angle);
	FRotator rotRing3 = caliRing3(angle);

	Matrix4f T_rotRing1 = transMatrixMakerZYX(rotRing1.Roll, rotRing1.Pitch, rotRing1.Yaw, 0., 0., 0.);
	Matrix4f T_rotRing2 = transMatrixMakerZYX(rotRing2.Roll, rotRing2.Pitch, rotRing2.Yaw, 0., 0., 0.);
	Matrix4f T_rotRing3 = transMatrixMakerZYX(rotRing3.Roll, rotRing3.Pitch, rotRing3.Yaw, 0., 0., 0.);

	ringLoc[2] = T_UtoWorld*T_L1toU*T_L2toL1*T_L3toL2*T_HtoL3*T_1toH_ring*T_rotRing1*T_2to1_ring*T_rotRing2*ringLoc[2];

	ringLocation[2] = FVector(ringLoc[2](0, 0), ringLoc[2](1, 0), ringLoc[2](2, 0));
	ringLocation[2] = skelToWorld.RotateVector(ringLocation[2]);

	ringLoc[3] = T_UtoWorld*T_L1toU*T_L2toL1*T_L3toL2*T_HtoL3*T_1toH_ring*T_rotRing1*T_2to1_ring*T_rotRing2*T_3to2_ring*T_rotRing3*ringLoc[3];
	ringLocation[3] = FVector(ringLoc[3](0, 0), ringLoc[3](1, 0), ringLoc[3](2, 0));
	ringLocation[3] = skelToWorld.RotateVector(ringLocation[3]);

	/*WCHAR buffer[300];
	swprintf(buffer, L"The fingertip is at (%f, %f, %f).\r\n The ring3 is at (%f, %f, %f).\r\n The distance is %f.\r\n", ringLocation[3].X, ringLocation[3].Y, ringLocation[3].Z, ringLocation[2].X, ringLocation[2].Y, ringLocation[2].Z, g_distance);
	OutputDebugString(buffer);*/

	Vector4f littleLoc[4];

	littleLoc[3] << 3., 0., 0., 1.;//估计末端指节长度为3.
	littleLoc[2] << 3.4, 0., 0., 1.;

	Matrix4f T_4to3_little = transMatrixMakerZYX(-1.286, -1.883, 28.486, 2.934, 0., 0.);
	Matrix4f T_3to2_little = transMatrixMakerZYX(1.515, 1.901, 47.209, 4.242, 0., 0.);
	Matrix4f T_2to1_little = transMatrixMakerZYX(16.690, -3.833, 27.889, 7.557, 0., 0.);
	Matrix4f T_1toH_little = transMatrixMakerZYX(0.940, 14.460, 3.761, 4.593, 0.042, 4.083);

	FRotator rotLittle1 = caliLittle1(angle);
	FRotator rotLittle2 = caliLittle2(angle);
	FRotator rotLittle3 = caliLittle3(angle);

	Matrix4f T_rotLittle1 = transMatrixMakerZYX(rotLittle1.Roll, rotLittle1.Pitch, rotLittle1.Yaw, 0., 0., 0.);
	Matrix4f T_rotLittle2 = transMatrixMakerZYX(rotLittle2.Roll, rotLittle2.Pitch, rotLittle2.Yaw, 0., 0., 0.);
	Matrix4f T_rotLittle3 = transMatrixMakerZYX(rotLittle3.Roll, rotLittle3.Pitch, rotLittle3.Yaw, 0., 0., 0.);

	littleLoc[2] = T_UtoWorld*T_L1toU*T_L2toL1*T_L3toL2*T_HtoL3*T_1toH_little*T_2to1_little*T_rotLittle1*T_3to2_little*T_rotLittle2*littleLoc[2];

	littleLocation[2] = FVector(littleLoc[2](0, 0), littleLoc[2](1, 0), littleLoc[2](2, 0));
	littleLocation[2] = skelToWorld.RotateVector(littleLocation[2]);

	littleLoc[3] = T_UtoWorld*T_L1toU*T_L2toL1*T_L3toL2*T_HtoL3*T_1toH_little*T_2to1_little*T_rotLittle1*T_3to2_little*T_rotLittle2*T_4to3_little*T_rotLittle3*littleLoc[3];
	littleLocation[3] = FVector(littleLoc[3](0, 0), littleLoc[3](1, 0), littleLoc[3](2, 0));
	littleLocation[3] = skelToWorld.RotateVector(littleLocation[3]);

	//WCHAR buffer[300];
	//swprintf(buffer, L"The fingertip is at (%f, %f, %f).\r\n The little3 is at (%f, %f, %f).\r\n The distance is %f.\r\n", littleLocation[3].X, littleLocation[3].Y, littleLocation[3].Z, littleLocation[2].X, littleLocation[2].Y, littleLocation[2].Z, g_distance);
	//OutputDebugString(buffer);



	
}

float angleGraphics[14];
int CollisionDetection() {

	
	int ret1 = IntersectHand(thumbLocation, ball, Cube, 0);
	if (ret1) {
		for (int i = 0; i<5; i++)
			OutputDebugString(L"thumb collision detection!\r\n");
	}

	int ret2 = IntersectHand(indexLocation, ball, Cube, 1);
	if (ret2) {
		for (int i = 0; i<5; i++)
			OutputDebugString(L"index collision detection!\r\n");
	}

	int ret3 = IntersectHand(middleLocation, ball, Cube, 2);
	if (ret3) {
		for (int i = 0; i<5; i++)
			OutputDebugString(L"middle collision detection!\r\n");
	}

	int ret4 = IntersectHand(ringLocation, ball, Cube, 3);
	if (ret4) {
		for (int i = 0; i<5; i++)
			OutputDebugString(L"ring collision detection!\r\n");
	}

	int ret5 = IntersectHand(littleLocation, ball, Cube, 4);
	if (ret5) {
		for (int i = 0; i<5; i++)
			OutputDebugString(L"little collision detection!\r\n");
	}

	int result_CD = ret1 | (ret2 << 1) | (ret3 << 2) | (ret4 << 3) | (ret5 << 4);
	return result_CD;
}

void GraphicsRendering(int result_CD) {
	int result1, result2, result3, result4, result5;
	result1 = result_CD & 0x01;
	result2 = result_CD & 0x02;
	result3 = result_CD & 0x04;
	result4 = result_CD & 0x08;
	result5 = result_CD & 0x10;
	if (result1) {

	}
	else {
		for (int i = 0; i < 3; i++) {
			angleGraphics[i] = angleHaptics[i];
		}
	}
	if (result2) {

	}
	else {
		for (int i = 3; i < 6; i++) {
			angleGraphics[i] = angleHaptics[i];
		}
	}
	if (result3) {

	}
	else {
		for (int i = 6; i < 8; i++) {
			angleGraphics[i] = angleHaptics[i];
		}
	}
	if (result4) {

	}
	else {
		for (int i = 8; i < 11; i++) {
			angleGraphics[i] = angleHaptics[i];
		}
	}
	if (result5) {

	}
	else {
		for (int i = 11; i < 14; i++) {
			angleGraphics[i] = angleHaptics[i];
		}
	}
}

float dist[5] = {};
float *ForceRendering() {

	FVector middleThumbHaptics = (thumbLocation[2] + thumbLocation[3]) / 2;
	FVector middleIndexHaptics = (indexLocation[2] + indexLocation[3]) / 2;
	FVector middleMiddleHaptics = (middleLocation[2] + middleLocation[3]) / 2;
	FVector middleRingHaptics = (ringLocation[2] + ringLocation[3]) / 2;
	FVector middleLittleHaptics = (littleLocation[2] + littleLocation[3]) / 2;
	
	CalHandOrient(angleGraphics);
	FVector middleIndexGraphics = (indexLocation[2] + indexLocation[3]) / 2;
	FVector middleThumbGraphics = (thumbLocation[2] + thumbLocation[3]) / 2;
	FVector middleMiddleGraphics = (middleLocation[2] + middleLocation[3]) / 2;
	FVector middleRingGraphics = (ringLocation[2] + ringLocation[3]) / 2;
	FVector middleLittleGraphics = (littleLocation[2] + littleLocation[3]) / 2;

	dist[0] = FVector::Dist(middleThumbHaptics, middleThumbGraphics);
	dist[1] = FVector::Dist(middleIndexHaptics, middleIndexGraphics);
	dist[2] = FVector::Dist(middleMiddleHaptics, middleMiddleGraphics);
	dist[3] = FVector::Dist(middleRingHaptics, middleRingGraphics);
	dist[4] = FVector::Dist(middleLittleHaptics, middleLittleGraphics);
	for (int i = 0; i < 5; i++) {
		if (dist[i] >= 20) {
			dist[i] = 20;
		}
	}


	WCHAR buffer[100];
	swprintf(buffer, L"The index's force is %f .\r\n", dist[1]);
	OutputDebugString(buffer);

	return dist;
}

void CloseHi5Glove() {

	{
		bReading = false;
		if (hi5DataReaderThread) {
			hi5DataReaderThread->join();
			delete hi5DataReaderThread;
			hi5DataReaderThread = nullptr;
		}
		if (hi5FetchStatusThread) {
			hi5FetchStatusThread->join();
			delete hi5FetchStatusThread;
			hi5FetchStatusThread = nullptr;
		}
		if (viveDataReaderThread) {
			viveDataReaderThread->join();
			delete viveDataReaderThread;
			viveDataReaderThread = nullptr;
		}
	}

	std::cout << "Stop dongle" << std::endl;
	hi5DongleStop();

	//exitCtrl.join();
}

