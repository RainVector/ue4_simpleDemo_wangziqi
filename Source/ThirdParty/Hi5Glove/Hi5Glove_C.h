/**
* @brief
*    Hi5Glove native C SDK is used to find and manage the dongle of Noitom Hi5 Glove, read dongle/glove status, data, and so on.
*/

#ifndef HI5GLOVE_C_API_H_
#define HI5GLOVE_C_API_H_

#include <Hi5Glove/HI5Glove_api.h>
#include "GloveDataType.h"

#ifdef __cplusplus
extern "C" {
#endif

namespace HI5Device
{
    /*******************************************************/
    /*           Global settings                           */
    /*******************************************************/  
    /**
    * @remark
    *   These callback settings must be applied before calling the function @refer hi5DongleStart(),
    *   otherwise, some callback events will not be received.
    */

    /**
    * @brief
    *    Set a function address as a callback handle to receive the status events of the dongle.
    * @param[in] object Custom defined object reference.
    * @param[in] handle Function will be called if the event is fired up in the library.
    * @remark
    *   Must be set before the @refer hi5DongleStart() is called.
    */
    HI5GLOVE_API void setDongleStateChangedHandle(void* object, DongleStateChangedCallback handle);

    /**
    * @brief
    *    Set a function address as callback handle to receive the status events of gloves.
    * @param[in] object Custom defined object reference.
    * @param[in] handle Function will be called if the event is fired up in the library.
    * @remark
    *   Must be set before the @refer hi5DongleStart() called.
    */
    HI5GLOVE_API void setGloveStateChangedHandle(void* object, GloveStateChangedCallback handle);

    /**
    * @brief
    *    Set a function address as callback handle to receiving the error code of BPose calibration.
    * @param[in] object Custom defined object reference.
    * @param[in] handle Function will be called if the event is fired up in the library.
    */
    HI5GLOVE_API void setBPoseCalibrationResultHandle(void* object, BPoseCalibrationResultCallback handle);

    /*******************************************************/
    /*           Dongle/glove settings                     */
    /*******************************************************/    
    /**
    * @brief
    *   Start to find and open a dongle.
    */
    HI5GLOVE_API void hi5DongleStart();
    
    /**
    * @brief
    *    Check whether a dongle is available.
    * @return TRUE means dongle is available, otherwise no dongle is available.
    */
    HI5GLOVE_API NBOOL isDongleAvailable();
    
    /**
    * @brief
    *   Get serial number of dongle.
    * @return Serial number of dongle. If no dongle is inserted, return an empty string.
    */
    HI5GLOVE_API const char* getDongleSN();

    /**
    * @brief
    *    Stop a dongle if it is available.
    */
    HI5GLOVE_API void hi5DongleStop();

    /**
    * @brief
    *   Demagnification factor of frequency of BVH output data. The default Demagnification factor is 2, means half of default data output.
    * @remark
    *   The capture frequency of Hi5Glove is 180Hz. So, if the demagnification factor is 1, all BVH frame data will be output. If it is 2,
    *   the output frequency is 90Hz, and so on. The value must be less or equal to 180.
    * @param[in] reduceCount Demagnification factor. If it is 'n', it should be: n>0 && n<=180.
    */
    HI5GLOVE_API void setReducedOutputDataFreq(unsigned int reduceCount);

    /**
    * @brief
    *   Set the thickness of the hand. It will be used to correct the distance of two hands at BPose calibration. Unit: meter, default value: 0.06m
    * @param[in] handThickness Set the thickness of hands.
    */
    HI5GLOVE_API void setHandThickness(float handThickness);

    /**
    * @brief
    *   Get the thickness of hand. Unit: meter, default value: 0.06m
    * @return Thickness of hands. Return '0.0' means no hand to getting data.
    * @remark Only if the dongle is available, the correct value can be received.
    */
    HI5GLOVE_API float getHandThickness();

    /**
    * @brief
    *   Set the position offset between the tracker and the wrist.
    * @param[in] leftTrackerOffset A float array buff(x,y,z) used to save the offset of the tracker
    * @param[in] rightTrackerOffset A float array buff(x,y,z) used to save the offset of the tracker
    */
    HI5GLOVE_API void setWristPositionInTrackerFrame(float* leftTrackerOffset/*xyz*/, float* rightTrackerOffset/*xyz*/);

    /**
    * @brief
    *   Get the position offset between the tracker and the wrist.
    * @param[out] leftTrackerOffset A float array buff(x,y,z) used to save the offset of the tracker
    * @param[out] rightTrackerOffset A float array buff(x,y,z) used to save the offset of the tracker
    */
    HI5GLOVE_API void getWristPositionInTrackerFrame(float* leftTrackerOffset/*xyz*/, float* rightTrackerOffset/*xyz*/);

    /**
    * @brief
    *   Set the rotation offset of the tracker in global system.
    * @param[in] in_q_bvh_to_opt A float array buff(s,x,y,z) used to save the offset from BVH to Optical system
    */
    HI5GLOVE_API void setBvhToOpt(float* in_q_bvh_to_opt/*sxyz*/);

    /**
    * @brief
    *   Get the rotation of tracker in global system.
    * @param[out] out_q_bvh_to_opt A float array buff(s,x,y,z) used to save the offset from BVH to Optical system
    */
    HI5GLOVE_API void getBvhToOpt(float* out_q_bvh_to_opt/*sxyz*/);

    /**
    * @brief
    *   Bind an Optical device to a hand with an identity string or SN of device.
    * @param[in] hand Refers to which hand will be applied with this setting. It only can be @refer GM_LeftGlove or @refer GM_RightGlove.
    * @param[in] sensorIdentity Identity of the device that will be bound to the hand. It can be any string or SN of device identity.
    * @param[in] sensorType Sensor type.
    * @remark
	*   If the binding relationship is not changed, the last relationship that was bound by @refer getOptiSensorBindState can be used. This can be used to avoid having to re-do BPose whenever restarted.
    */
    HI5GLOVE_API void setOptiSensorBindState(GloveMod hand, char* sensorIdentity, OpticalSensorType sensorType);

    /**
    * @brief
    *   Get the SN of optical sensor bound to the hand.
    * @param[in] hand Left hand or right hand. It only can be @refer GM_LeftGlove or @refer GM_RightGlove.
    * @param[out] buffer Used to receive SN. Normally the length of a SN is 12 bytes, recommended length is 64 bytes.
    * @param[in] buffLen Length of the buffer used to receive SN. Normally the length of a SN is 12 bytes, recommended length is 64 bytes.
    * @param[out] sensorType Sensor type.
    * @return Length of SN.
    * @remark 
    *   It is recommended to save the binding relationship after each calibration so that the next time you can restore the binding relationship to avoid recalibration.
    */
    HI5GLOVE_API int getOptiSensorBindState(GloveMod hand, char* buffer, unsigned int buffLen, OpticalSensorType* sensorType);

    /**
    * @brief
    *   Get dongle/receiver firmware version
    * @param[out] buffer Used to receive dongle information.
    * @return true, successful. Otherwise it means there was a timeout.
    */
    HI5GLOVE_API NBOOL getDongleFirmwareVersion(DongleFirmwareVersion* buffer);

    /**
    * @brief
    *   Get firmware version of left and right gloves
    * @param[out] left Used to receive firmware version of left glove. If no left glove, the 'gloveType' will be set to 'GM_Unknown'
    * @param[out] right Used to receive firmware version of right glove. If no right glove, the 'gloveType' will be set to 'GM_Unknown'
    * @return true, successful if one or both glove versions got. Otherwise it means there was a timeout.
    */
    HI5GLOVE_API NBOOL getGloveFirmwareVersion(GloveFirmwareVersion* left, GloveFirmwareVersion* right);

    /**
    * @brief
    *   Get power level
    * @param[out] leftGlove A buffer used to receiving the power value.
    * @param[out] rightGlove A buffer used to receiving the power value.
    * @return true, successful. Otherwise it means there was a timeout.
    * @remark
    *   Power level value:
    *   - 0:No power information
    *   - 1:Low power
    *   - 2:Normal
    *   - 3:Full
    */
    HI5GLOVE_API NBOOL getGlovesPowerLevel(int* leftGlove, int* rightGlove);

    /**
    * @brief
    *   Get current working band
    * @return Current radio freq. -1 means timeout
    */
    HI5GLOVE_API int getCurrentRadioFrequency();

    /**
    * @brief
    *   Get dongle running mode
    * @return A @refer DongleRunningMode. 'Running_In_Unknown' means it failed.
    */
    HI5GLOVE_API DongleRunningMode getDongleRunningMode();

    /**
    * @brief
    *   Enable left glove to vibrate for a certain amount of time.
    * @param[in] timeSpan Vibration time, unit: millisecond.
    */
    HI5GLOVE_API void enableLeftGloveVibrator(unsigned int timeSpan/*ms*/);

    /**
    * @brief
    *   Enable right glove to vibrate for a certain amount of time.
    * @param[in] timeSpan Vibration time, unit: millisecond.
    */
    HI5GLOVE_API void enableRightGloveVibrator(unsigned int timeSpan/*ms*/);

    /**
    * @brief
    *   Enable two gloves to vibrate for a certain amount of time.
    * @param[in] leftTimeSpan Vibration time of left glove, unit: millisecond.
    * @param[in] rightTimeSpan Vibration time of right glove, unit: millisecond.
    */
    HI5GLOVE_API void enableGlovesVibrator(unsigned int leftTimeSpan/*ms*/, unsigned int rightTimeSpan/*ms*/);

    /**
    * @brief
    *   Get the radio frequency list that the dongle can use to communicate with the gloves.
    * @param[out] freqTab An int array used to receive the list of radio frequencies. The array length is 32.
    * @return The number of radio frequencies.
    */
    HI5GLOVE_API int getDongleRadioFrequencyTable(unsigned int freqTab[32]);

    /**
    * @brief
    *   Set radio frequency of dongle.
    * @remark The dongle will randomly select a radio frequency to communicate with the gloves when it starts.
    *   If the current radio frequency is interfering with other devices, the dongle will change to another one in the frequency table automatically.
    *   If you want to lock the frequency, call this function to refer a value in the frequency table. This enables the dongle to use the referred
    *   radio frequency and will not change the frequency automatically any more, even if re-inserted to the PC.
    *   Use '0xff' to unlock the radio frequency of dongle.
    * @param[in] freq Radio frequency, one of the radio frequencies in the table, unit: Hz
    */
    HI5GLOVE_API NBOOL setDongleRadioFrequency(unsigned int freq);

    /*******************************************************/
    /*        Optical data input interface.                */
    /*******************************************************/
    /**
    * @brief
    *   Input optical sensor data.
    * @param[in] sensorIdentity SN or any string used as an identity.
    * @param[in] type Optical sensor device type.
    * @param[in] pos Position of sensor in optical system
    * @param[in] quat Rotation of sensor in optical system
    */
    HI5GLOVE_API void pushOpticalSensorData(char* sensorIdentity, OpticalSensorType type, float* pos/*xyz*/, float* quat/*sxyz*/);

    /**
    * @brief
    *   Another type
    * @param[in] handType Left hand or right hand.
    * @param[in] type Optical sensor type
    * @param[in] pos Position of sensor in optical system
    * @param[in] quat Rotation of sensor in optical system
    */
    HI5GLOVE_API void pushOpticalSensorDataWithHandType(GloveMod handType, OpticalSensorType type, float* pos/*xyz*/, float* quat/*sxyz*/);

    /*******************************************************/
    /*      Output: the Hi5Glove fusion result. BVH format */
    /*******************************************************/
    /**
    *@brief
    *  Get the Hi5Glove gesture data, BVH format.  Only one glove data can be received at once. 
	*  The param of bUpdate is set to be true if the data is the latest received, otherwise it is false.
    *@param[out] dataBuff Used to receive the gesture data. It can only be @refer GloveBVHData.
    *@remark
	*   Must determine whether 'bUpdate' is true or false before using it. If there is no latest received data, other fields are meaningless and can be discarded.
	*   The latest received data will be overwritten if the data is not read in time. The loss of data can be detected by 'frameIndex' of @refer GloveBVHData
    **/
    HI5GLOVE_API void readBVHData(GloveBVHData* dataBuff);

    /**
    * @brief
	*   Get the status of the device
    * @param[out] dataBuff Used to receive the status data. It only can be @refer HI5GloveStatus
    */
    HI5GLOVE_API void readDeviceStatus(HI5GloveStatus* dataBuff);


    /*******************************************************/
    /*        Gloves calibration                           */
    /*******************************************************/

    /**
    * @brief 
    * @remark The error information of BPose calibration is output via a callback. A callback must be registered if the result of BPose calibration is needed.
    */

    /**
    * @brief
    *   Reset calibration action and clear calibration data before the next series of calibration *actions
    * @remark
    *   The API must to be used to Reset or clear the last calibration data before the next series of calibration actions.
    */
    HI5GLOVE_API void calibrationPrepare();

    /**
    * @brief
	*   Start the calibration procedure of a specified calibration action. Once the action is started, the calibration data for this action is buffered until the preset buffer is full.
    *   The calibration percent can be retrieved by @refer getCalibrationPercent
    * @param[in] posture Calibration posture
    * @remark
	*   It will take about 15 to 20 seconds to calibrate the BPose.
    */
    HI5GLOVE_API void startCalibration(CalibrationPose pose);

    /**
    * @brief
    *   Get the percent of calibration
    * @param[in] pose @refer CalibrationPose
    * @return The progress data of calibration 
    * example
    *   CalibrationPercent cp = getCalibratingPercent(HI5Device::GCP_CPose);
    *   printf("pose %d, percent %d\n", cp.pos, cp.percent);
    */
    HI5GLOVE_API CalibrationPercent getCalibratingPercent(CalibrationPose pose);

	/**
	* @brief 
	*    Load the calibration data. The last calibration data can be loaded if the gesture of the hand and the position offset of the sensor have no obvious changes.
	* @return
	*   True, successful. It will fail if the file does not exist or the loading file is not a calibration file.
	*   It will be calibrated using a set of default data of bone and bone1 if it fails. 
    * @remark
	*   Must be loaded  after finding the device.
	*/
    HI5GLOVE_API NBOOL loadCalibrationData(char* file_name);
    /**
    * @brief
	*   Save the resulting data of the calibration to a file. The result can be directly used to load at the next start.
    * @return
	*   True if successful. Fail if the upper directory of the file does not exist or the file is already occupied.
    * @remark
    *   It will be automatically saved to the last loaded file when the calibration is completed.
    */
    HI5GLOVE_API NBOOL saveCalibrationData(char* file_name);

} // namespace HI5Device

#ifdef __cplusplus
}
#endif


#endif //!HI5GLOVE_C_API_H_