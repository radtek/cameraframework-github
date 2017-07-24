
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_OTHERCAMERADRIVERPROVIDER_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_OTHERCAMERADRIVERPROVIDER_H__

#include "CameraDriverProvider.h"

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
    //VOID SetParam() override;
    //VOID AllocMemory() override;
    Int32 GetCapture() override;
    Int32 StopCapture() override;
    Int32 CloseDriver() override;
    Int32 InitDevice() override;
    Int32 UninitDevice() override;

    VOID ShowInfo() override;


    VOID update() override;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_OTHERCAMERADRIVERPROVIDER_H__