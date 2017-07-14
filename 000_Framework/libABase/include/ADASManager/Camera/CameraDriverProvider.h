
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
    virtual Int32 OpenDriver() = 0;
    virtual VOID SetParam() = 0;
    virtual VOID AllocMemory() = 0;
    virtual VOID GetCapture() = 0;
    virtual VOID CloseDriver() = 0;

    virtual VOID ShowInfo() = 0;

public:
    virtual Int32 OpenCamera() final;

    virtual Int32 CloseCamera() final;   // just stop provider data, do not close(fd)

    virtual Int32 PowOffCamera() final;  // close(fd)

    virtual ~CameraDriverProvider() {}

protected:
    Int32 m_iFd = -1;
    BOOLEAN m_bIsOpened = FALSE;

    const string m_strCameraName;
    const string m_strDriverPath;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERADRIVERPROVIDER_H__