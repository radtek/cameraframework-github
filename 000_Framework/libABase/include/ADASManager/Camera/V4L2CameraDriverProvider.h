
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_V4L2CAMERADRIVERPROVIDER_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_V4L2CAMERADRIVERPROVIDER_H__

#include "CameraDriverProvider.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class V4L2CameraDriverProvider : public CameraDriverProvider
{
public:
    V4L2CameraDriverProvider(const string& cameraName);

    ~V4L2CameraDriverProvider();

    int OpenDriver() override;
    void SetParam() override;
    void AllocMemory() override;
    void GetCapture() override;
    void CloseDriver() override;

    BOOLEAN IsOpen() override;
    void ShowInfo() override;

};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_V4L2CAMERADRIVERPROVIDER_H__