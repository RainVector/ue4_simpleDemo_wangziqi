#pragma once

#ifndef _DATA_TYPE_H_
#define _DATA_TYPE_H_

//#include <stdint.h>
#include <vector>

namespace HI5Device
{


/**
* @brief
*   Macro definitions
*/
#define DATA_FREQUENCY              180             ///< Hardware output data frequency, Hz
#define CALIBRATION_POSE_NUMB       5               ///< All calibration postures:APose,TPose,PPose,BPose,CPose

#ifndef NBOOL
#define NBOOL                       int             ///< Bool type
#endif // !NBOOL

#ifndef TRUE
#define TRUE                        1               ///< const 'True'
#endif // !TRUE

#ifndef FALSE
#define FALSE                       0               ///< const 'False'
#endif // !TRUE


/**
* @brief
*   Errors definition of HI5 SDK
*/

#define EHI_OK                      0               ///< No error.
#define EHI_SteamVRNotStart         0x100           ///< 
#define EHI_UNKONWN                 0XFFFFFFFF      ///< Unkonwn error.

/*
* @brief Enums of Hi5 SDK
*/

/**
* @brief
*   Left fingers or bone index in its bvh data array.
*/
typedef enum _LeftFingers
{
    LeftForeArm = 0,                    ///< Left forearm
    LeftHand,                           ///< Left hand
    LeftHandThumb1,                     ///< Left hand thumb1
    LeftHandThumb2,                     ///< Left hand thumb2
    LeftHandThumb3,                     ///< Left hand thumb3
    LeftInHandIndex,                    ///< Left in hand index
    LeftHandIndex1,                     ///< Left hand index1
    LeftHandIndex2,                     ///< Left hand Index2
    LeftHandIndex3,                     ///< Left hand Index3
    LeftInHandMiddle,                   ///< Left in hand middle
    LeftHandMiddle1,                    ///< Left hand Middle1
    LeftHandMiddle2,                    ///< Left hand Middle2
    LeftHandMiddle3,                    ///< Left hand Middle3
    LeftInHandRing,                     ///< Left in hand Ring
    LeftHandRing1,                      ///< Left hand Ring1
    LeftHandRing2,                      ///< Left hand Ring2
    LeftHandRing3,                      ///< Left hand Ring3
    LeftInHandPinky,                    ///< Left in hand Pinky
    LeftHandPinky1,                     ///< Left hand Pinky1
    LeftHandPinky2,                     ///< Left hand Pinky2
    LeftHandPinky3,                     ///< Left hand Pinky3
    LeftHandBoneMaxNumb,                ///<  Max number of this enum
}LeftFingers;

/**
* @brief
*   Right fingers or bone index in its bvh data array.
*/
typedef enum _RightFingers
{
    RightForeArm = 0,                   ///< Right ForeArm
    RightHand,                          ///< Right hand
    RightHandThumb1,                    ///< Right hand thumb1
    RightHandThumb2,                    ///< Right hand thumb2
    RightHandThumb3,                    ///< Right hand thumb3
    RightInHandIndex,                   ///< Right in hand index
    RightHandIndex1,                    ///< Right hand index1
    RightHandIndex2,                    ///< Right hand index2
    RightHandIndex3,                    ///< Right hand index3
    RightInHandMiddle,                  ///< Right in hand middle
    RightHandMiddle1,                   ///< Right hand middle1
    RightHandMiddle2,                   ///< Right hand middle2
    RightHandMiddle3,                   ///< Right hand middle3
    RightInHandRing,                    ///< Right in handRing
    RightHandRing1,                     ///< Right hand ring1
    RightHandRing2,                     ///< Right hand ring2
    RightHandRing3,                     ///< Right hand ring3
    RightInHandPinky,                   ///< Right in hand pinky
    RightHandPinky1,                    ///< Right hand pinky1
    RightHandPinky2,                    ///< Right hand pinky2
    RightHandPinky3,                    ///< Right hand pinky3
    RightHandBoneMaxNumb,               ///<  Max number of this enum
}RightFingers;

/**
* @brief
*   As a parameter will appears with its output data
*/
typedef enum _GloveMod
{
    GM_Unknown = -1,        ///< Unknown mod
    GM_BothGloves,          ///< Both gloves
    GM_LeftGlove,           ///< Left glove
    GM_RightGlove,          ///< Right glove
    GM_MaxNumb,             ///<  Max number of this enum
}GloveMod;

/**
* @brief
*   Calibration types
*/
typedef enum _CalibrationPose
{
    GCP_Unknown = -1,   ///< Unknown pose
    GCP_TPose,          ///< Standing like a letter 'T'
    GCP_APose,          ///< Standing like a letter 'A'
    GCP_PPose,          ///< Pinch pose of hand, like an 'OK' posture.
    GCP_BPose,          ///< Buddha pose
    GCP_CPose,          ///< Buddha pose and moving hands infront of chest
    GCP_MaxNumb,        ///<  Max number of this enum
}CalibrationPose;

/** @brief
*   Dongle running mode: App mod or Boot mode
*/
typedef enum _DongleRunningMode
{
    Running_In_Unknown = -1,    ///< unknown running mode
    Running_In_App,             ///< Running in app mode
    Running_In_Boot,            ///< Running in boot mode
    Running_MaxNumb,            ///<  Max number of this enum
}DongleRunningMode;


/**
* @brief
*   Dongle or glove status.
*/
typedef enum _HI5GloveStatus
{
    DV_Unknown = -1,            ///< Unknown status
    DV_NoDongle,                ///< No dongle inserted
    DV_NoGlove,                 ///< No glove can be used
    DV_LeftGloveAvailable,      ///< Left glove is available
    DV_RightGloveAvailable,     ///< Right glove is available
    DV_BothGloveAvailable,      ///< Both gloves are available
    DV_MaxNumb,                 ///< Max number of this enum
}HI5GloveStatus;


/**
* @brief
*   Optical sensor types used in this system, if available.
*/
typedef enum _OpticalSensorType
{
    OST_Unknown = -1,           ///< Unknown device type
    OST_HTC_VIVE_Tracker,       ///< Vive tracker
    OST_HTC_VIVE_Controller,    ///< Vive controller
    OST_Alice_Rigid_Body,       ///< Alice rigid body
    OST_Microsoft_MR_Controller,///< Microsoft MR controller
    OST_MaxNumb,                ///< Max number of this enum
}OpticalSensorType;


/**
* @brief
*   Errors number of BPose calibration.
*/
typedef enum _BPoseCalibrationErrors
{
    BE_NotCalibrated = -1,  ///< Not calibrated
    BE_CalibratedOK,        ///< The calibration is successful
    BE_NoImuData,           ///< No imu data
    BE_NoOptiData,          ///< No optical data
    BE_WrongBPoseAction,    ///< The range of BPose moving is too small. Or, the optical data is not enough. Or, the BPose action is too quick or too slow
    BE_BindingFailed,       ///< The bind between Optical sensor and HI5Glove failed.
    BE_MatchFailed,         ///< The bind relationship does not match with the mode of HI5Glove
    BE_OptiImuCalcFailed,   ///< The calculation of the relationship between the Optical and Imu failed.
    BE_MaxNumb,             ///< Max number of this enum
}BPoseCalibrationErrors;

/******************************************************************************/
/*  Data type and structs                                                     */
/******************************************************************************/
#pragma pack(push, 1)

/**
* @brief
*   Version number
*/
typedef struct _Ver
{
    int major;         ///< Major number
    int minor;         ///< Minor number
    int rev;           ///< Rev number
    int build;         ///< Build number
}Ver;

/**
* @brief
*   Dongle HID information
*/
typedef struct _DongleInentity
{
    unsigned short VID;     ///< VID
    unsigned short PID;     ///< PID
    char SerialNumber[260]; ///< SN of dongle
    char DevicePath[260];   ///< path of dongle in driver system
}DongleIdentity;

/**
* @brief
*   Dongle information
*/
typedef struct _DongleFirmwareVersion
{
    Ver  bootVer;           ///< Boot version number
    Ver  appVer;            ///< App version number
}DongleFirmwareVersion;

/**
* @brief
*   Glove information
*/
typedef struct _GloveFirmwareVersion
{
    GloveMod gloveType;     ///< The firmware version of the glove, @refer GM_LeftGlove or @refer GM_RightGlove
    Ver bootVer;            ///< Boot version of glove
    Ver appM0Ver;           ///< M0 version of glove
    Ver appM4Ver;           ///< M4 version of glove
}GloveFirmwareVersion;

/**
* @brief
*   Time stamp of data
*/
typedef struct _TimeStamp
{
    double timeStamp;  ///< ms, from 1970, time stamp when data gathered
    double latency;    ///< ms, calculation time
}TimeStamp;

/**
* @brief
*   BVH data of a glove
* @remark
*   If 'bWithDisp=true', every bone with 6DOF: Xposition Yposition Zposition Yrotation Xrotation Zrotation, otherwise its 3DOF: Yrotation Xrotation Zrotation.
*   The root node is always 6DOF.
*/
typedef struct _GloveBVHData
{
    GloveMod glove;       ///< Only 'GM_LeftGlove' or 'GM_RightGlove' in data, means this frame comes from left or right glove
    TimeStamp timeStamp;  ///< Time stamp
    NBOOL bUpdate;        ///< TRUE means new data updated by device
    int bWithDisp;        ///< Whether the BVH node has displacement
    int frameIndex;       ///< Frame index
    int dataCount;        ///< Number of data by float array
    float data[160];      ///< BVH data array
}GloveBVHData;

/**
* @brief
*   Calibration posture and its percentage
*/
typedef struct _CalibrationPercent
{
    CalibrationPose pos;        ///< Calibration posture
    int             percent;    ///< Calibration percentage
}CalibrationPercent;

#pragma pack(pop)


/******************************************************************************/
/*  Callback event handles                                                    */
/******************************************************************************/

/**
* @brief
*   Enumerate types of dongle events
*/
enum DongleEvent
{
    DE_Insert,              ///< Inserted a dongle
    DE_Removed,             ///< Removed a dongle
};

/**
* @brief
*   Enumerate types of glove events
*/
enum GloveEvent
{
    GE_Unknown = -1,
    GE_LowPower,            ///< Low power
    GE_NormalPower,         ///< Normal power
    GE_FullPower,           ///< Full power
    GE_NotMagneticed,       ///< Not magnetized
    GE_Magneticed,          ///< Magnetized
    GE_RadioFrequencyChanged,   ///<  Frequency of radio changed
    GE_MaxNumb,             ///< Max number of this enum
};

/**
* @brief
*   Callback. Used to receive the events about whether the dongle has been inserted or removed.
* @param[out] userData   A custom param. If the callback is set to be static, the 'this' is passed in through @userData. And 'this' can be converted into a class pointer, which will be convenient to access the class members or variables.
* @param[out] hid       The HID informations of the dongle.
* @param[out] action    The event about whether it was inserted or removed.
*/
typedef void(__stdcall *DongleStateChangedCallback)(void* userData, const DongleIdentity* hid, DongleEvent action);

/**
* @brief
*   Callback. Used to receive the power changes and Magnetization of the Hi5Glove.
* @param[out] userData   A custom param. If the callback is set to be static, the 'this' is passed in through @userData. And 'this' can be converted into a class pointer, which will be convenient to access the class members or variables.
* @param[out] glove      Which glove's event 
* @param[out] event     The event type @refer GloveEvent
*/
typedef void(__stdcall *GloveStateChangedCallback)(void* userData, GloveMod glove, GloveEvent event);

/**
* @brief
*   Callback. Used to receive the result of the BPose.
* @param[out] userData   A custom param. If the callback is set to be static, the 'this' is passed in through @userData. And 'this' can be converted into a class pointer, which will be convenient to access the class members or variables.
* @param[out] result    The BPose calibration result or the failure reason.
*/
typedef void(__stdcall *BPoseCalibrationResultCallback)(void* userData, BPoseCalibrationErrors result);

} // namespace HI5Device

#endif // !_DATA_TYPE_H_
