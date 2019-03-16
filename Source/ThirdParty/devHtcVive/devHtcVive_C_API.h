#ifndef _DEVHTCVIVE_C_API_H
#define _DEVHTCVIVE_C_API_H


#include "devHtcVive_api.h"
#include "DataType.h"

#ifdef __cplusplus
extern "C" {
#endif

namespace ViveSystem
{
    /**
    *  @brief
    *    Init library
    */
    DEVHTCVIVE_API bool initViveLib(DeviceStatus& errnumb);

    /**
    *  @brief
    *    Release library
    */
    DEVHTCVIVE_API void releaseViveLib();

    /**
    *  @brief
    *    Set a function piont to receive events about device status changing.
    */
    DEVHTCVIVE_API void setDeviceStatusChangedHandle(DeviceStatusChangedHandle handle);

    /**
    *  @brief
    *    TBD
    */
    DEVHTCVIVE_API void setTrackingMod(TrackingMod mod);

    /* @brief
    *   Set data frequency
    * @param freq A number of data frequency, Hz, must be greater than 0. Default is 180Hz.
    * @remark '0' will be convert to max freq, means 1000Hz.
    */
    DEVHTCVIVE_API void setFreq(unsigned int freq);

    /**
    *  @brief
    *    Read data
    */
    DEVHTCVIVE_API void readViveData(TrackedDevicePose dataBuffer[16], DeviceStatus& errnumb);

    /**
    *  @brief
    *    Read status
    */
    DEVHTCVIVE_API void readViveStatus(DeviceStatus* statusBuffer);


} // namespace ViveSystem

#ifdef __cplusplus
}
#endif

#endif // !_DEVHTCVIVE_C_API_H