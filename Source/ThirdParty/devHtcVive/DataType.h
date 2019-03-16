#ifndef _DATATYPE_H
#define _DATATYPE_H


#include <stdint.h>


namespace ViveSystem
{
     /******************************************************
     *               Micro definitions                     *
     *******************************************************/
    #define MAX_DEVICE_COUNT    16    // 

     /******************************************************
     *               Device status definitions             *
     *******************************************************/
     /**
     *  @brief
     *    Device status number list
     */
    typedef enum _DeviceError
    {
        DevStatus_OK = 0,

        DevStatus_Init_SystemNotInitialized = 100,
        DevStatus_Init_SteamVRNotRunning = 101,
        DevStatus_Init_NoDeviceHandleRefered = 102,
        DevStatus_Init_InvalidateDeviceHandle = 103,
        DevStatus_Init_HMDInUse = 104,

        DevStatus_Data_NoValidateDataCanBeRead = 200,
        DevStatus_Data_HMDInvalidate = 201,
        DevStatus_Data_HMDPoseInvalidate = 202,
        DevStatus_Data_ControllerInvalidate = 203,
        DevStatus_Data_BufferIsNotEnough = 204,

        DevStatus_Unknown = 0x0FFFFFFF,
    }DeviceStatus;


     /******************************************************
     *                Data type definitions                *
     *******************************************************/
     /**
     *  @brief
     *    TBD
     */
    typedef enum _TrackingMod
    {
        TM_Seated = 0,      // 座位模式, Poses are provided relative to the seated zero pose
        TM_Standing = 1,    // 站立模式, Poses are provided relative to the safe bounds configured by the user
    }TrackingMod;

    /**
    *  @brief
    *    设备事件
    */
    typedef enum _DeviceEvent
    {
        DE_UnknownEvent,
        DE_SteramVRNotRunning,
        DE_SteramVRStarted,
        DE_HMDConnected,
        DE_HMDDisconnected,
        DE_ControllerConnected,
        DE_ControllerDisconnected,
        DE_TrackerConnected,
        DE_TrackerDisconnected,
        DE_IndexChanged,
    }DeviceEvent;

    /**
    *  @brief
    *    TBD
    */
    typedef enum _DeviceDataType
    {
        DT_Unknown,
        DT_HMD,
        DT_Controller,
        DT_Tracker,
    }DeviceDataType;

    /**
    *  @brief
    *    TBD
    */
    typedef enum _QuaternionRotationOrder
    {
        QR_XYZ,
        QR_YXZ,
        QR_XZY,
        QR_ZXY,
        QR_YZX,
        QR_ZYX,
    }QuaternionRotationOrder;

    #pragma pack(push, 1)

    /**
    *  @brief
    *    TBD
    */
    typedef struct _TrackedDevicePose
    {
        char strSN[64];                     // 
        int nIndex;                         // 
        DeviceDataType eDataType;           // 
        int  bPoseValid;                    // Is data validate: '1' means the readed pose is valid, or it is old data.
        float fTimeStamp;                   // time stamp from application start
        float fPosition[3];                 // Absolute tracking position, x,y,z
        float fRotation[4];                 // Rotation, s,x,y,z
        float fVelocity[3];				    // Velocity in tracker space in m/s
        float fAngularVelocity[3];		    // Angular velocity in radians/s (?)
        float fPoseMatrix[3][4];            // Absolute tracking position, rotation. The last column is position.
    }TrackedDevicePose;

    /**
    *  @brief
    *    TBD
    */
    typedef struct _TrackedDevicePoseEx
    {
        char strSN[64];                     // 
        int nIndex;                         // 
        DeviceDataType eDataType;           // 
        int  bPoseValid;                    // Is data validate: '1' means the readed pose is valid, or it is old data.
        float fTimeStamp;                   // 
        float fPoseMatrix[3][4];            // Absolute tracking position, rotation. The last column is position.
        float fVelocity[3];				    // Velocity in tracker space in m/s
        float fAngularVelocity[3];		    // Angular velocity in radians/s (?)
    }TrackedDevicePoseEx;

    /**
    *  @brief
    *    TBD
    */
    typedef struct _DeviceEventArg
    {
        char strSN[64];                     // 
        int nNewIndex;                      // 
        int nOldIndex;                      // 
    }DeviceEventArg;

    #pragma pack(pop)

    /**
    *  @brief
    *   回调输出当前已经配对的设备数量、设备插入、拔除、index变化等事件
    * @param
    *   -[out] devCount，当前已配对的设备数量
    *   -[out] sEvent，DeviceEvent类型，包括设备插、拔除等事件
    *   -[out] arg，事件参数，包括当前触发此事件的设备SN、新、旧Index
    */
    typedef void(*DeviceStatusChangedHandle)(int devCount, DeviceEvent sEvent, DeviceEventArg arg);

} // !namespace ViveSystem


#endif // !_DATATYPE_H