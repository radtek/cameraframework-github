
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERADRIVERPROVIDER_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERADRIVERPROVIDER_H__

#include "TypeDefine.h"
#include "CameraDriverProviderFactory.h"
#include "CRunableBase.h"

using Harman::Adas::AFramework::AFoundation::CRunableBase;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class CameraDriverProvider : public CRunableBase
{
public:
    CameraDriverProvider(const string& cameraName)
        : CRunableBase(cameraName, FALSE)
        , m_strCameraName(cameraName)
        , m_strDriverPath(CameraDriverProviderFactory::m_mapCameraMapDevicePath[cameraName])
    {}

protected:
    virtual Int32 OpenDriver() = 0;
    virtual Int32 CloseDriver() = 0;

    virtual Int32 InitDevice() = 0;
    virtual Int32 UninitDevice() = 0;

    virtual Int32 GetCapture() = 0;
    virtual Int32 StopCapture() = 0;

    virtual VOID ShowInfo() = 0;

public:
    virtual Int32 OpenCamera() final;   // open(fd) AND Init_device() AND GetCapture()

    // if isReal == FALSE : CloseCamera just CALL StopCapture, do not CALL Uninit_device() && close(fd)
    // if isReal == TRUE  : CloseCamera will CALL StopCapture AND Uninit_device() AND close(fd)
    virtual Int32 CloseCamera(const BOOLEAN isReal) final;  // close(fd)

    virtual ~CameraDriverProvider() {}

protected:
    Int32 m_iFd = -1;
    BOOLEAN m_bIsOpened = FALSE;
    BOOLEAN m_bHasInit = FALSE;

    const string& m_strCameraName;
    const string& m_strDriverPath;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERADRIVERPROVIDER_H__