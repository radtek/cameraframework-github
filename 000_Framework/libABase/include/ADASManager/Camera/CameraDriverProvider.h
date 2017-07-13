
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERADRIVERPROVIDER_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERADRIVERPROVIDER_H__

#include "TypeDefine.h"
#include "CameraDriverProviderFactory.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class CameraDriverProvider
{
public:
    CameraDriverProvider(const string& cameraName)
        : m_strCameraName(cameraName)
        , m_strDriverPath(CameraDriverProviderFactory::m_mapCameraMapDevicePath[cameraName])
    {}

protected:
    virtual int OpenDriver() = 0;
    virtual void SetParam() = 0;
    virtual void AllocMemory() = 0;
    virtual void GetCapture() = 0;
    virtual void CloseDriver() = 0;
    virtual BOOLEAN IsOpen() = 0;

    virtual void ShowInfo() = 0;

public:
    int OpenCamera();

    int CloseCamera();

    virtual ~CameraDriverProvider() {}

protected:
    Int32 m_iFd = -1;
    const string m_strCameraName;
    const string m_strDriverPath;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERADRIVERPROVIDER_H__