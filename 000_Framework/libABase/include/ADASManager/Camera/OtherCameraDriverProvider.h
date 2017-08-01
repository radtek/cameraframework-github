
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_OTHERCAMERADRIVERPROVIDER_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_OTHERCAMERADRIVERPROVIDER_H__

#include "CameraDriverProvider.h"
#include "CameraDriverProviderFactory.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

// reserve for extend
// if OtherCameraDriverProvider is a industrial standard like V4L2, then just put here.
// if OtherCameraDriverProvider ia a platform specifically, then put it in project is more appropriate than others
class OtherCameraDriverProvider : public CameraDriverProvider
{
public:
    OtherCameraDriverProvider(const string& cameraName);

    ~OtherCameraDriverProvider();

    Int32 OpenDriver() override;
    Int32 CloseDriver() override;

    Int32 InitDevice() override;
    Int32 UninitDevice() override;

    Int32 GetCapture() override;
    Int32 StopCapture() override;

    VOID ShowInfo() override;
    VOID update() override;
};

class OtherCameraDriverProviderFactory : public CameraDriverProviderFactory
{
public:
    CameraDriverProvider* CreateCameraDriverProvider(const string& cameraName) override {
        return new OtherCameraDriverProvider(cameraName);
    }
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_OTHERCAMERADRIVERPROVIDER_H__