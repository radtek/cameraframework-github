
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