
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERADRIVERFACTORY_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERADRIVERFACTORY_H__

#include <map>
#include "TraceMacros.h"
#include "CameraEventDefine.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class CameraDriverProvider;

// //reserve for extend
// //if OtherCameraDriverProvider is a industrial standard like V4L2, then just put here.
// //if OtherCameraDriverProvider ia a platform specifically, then put it in project is more appropriate than others
// class OtherCameraDriverProvider : public CameraDriverProvider
// {
// public:
//     OtherCameraDriverProvider(const string& cameraName)
//         : CameraDriverProvider(cameraName)
//     {
//     }

//     int OpenDriver() { ALOGI("Not Implement, just a template for extending other way to talk with camera driver! \n"); return 0;}
//     void SetParam() { ALOGI("Not Implement, just a template for extending other way to talk with camera driver! \n"); }
//     void AllocMemory() { ALOGI("Not Implement, just a template for extending other way to talk with camera driver! \n"); }
//     void GetCapture() { ALOGI("Not Implement, just a template for extending other way to talk with camera driver! \n"); }
//     void CloseDriver() { ALOGI("Not Implement, just a template for extending other way to talk with camera driver! \n"); }

//     BOOLEAN IsOpen() { ALOGI("Not Implement, just a template for extending other way to talk with camera driver! \n"); }
//     void ShowInfo() { ALOGI("Not Implement, just a template for extending other way to talk with camera driver! \n"); }
// };

class CameraDriverProviderFactory
{
public:
    static CameraDriverProvider* CreateCameraDriverProvider(const string& cameraName);

public:
    static map<string, Enum_TheWayToTalkWithCameraDriver> m_mapCameraMapProvider;
    static map<string, string> m_mapCameraMapDevicePath;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERADRIVERFACTORY_H__