
#ifndef __HARMAN_ADAS_APROJECT_GWMV2MH_CAMERA_CAMERAHUBGWMV2_H__
#define __HARMAN_ADAS_APROJECT_GWMV2MH_CAMERA_CAMERAHUBGWMV2_H__

#include "ADASManager/Camera/Camera.h"
#include "ADASManager/Camera/CameraHub.h"

#include <map>
#include <thread>
#include "AFoundation.h"

using namespace Harman::Adas::AFramework::AFoundation;

using namespace std;

using Harman::Adas::AFramework::ABase::ADASManager::Camera;
using Harman::Adas::AFramework::ABase::ADASManager::CameraHub;

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {
namespace Camera {

class CameraHubGWMv2 : public CameraHub
{
public:
    /******** cameraCreatFlag :  which model need which cameras *****
     * BIT : 1:need  /  0:no need  /  X:reserve
     * BYTE : X      X      X      X      1/0    1/0   1/0  1/0
     *                                  (front reserve left right)
     * eg :  rvc: 0000 0100
     *       svc: 0000 0001
     *       avm: 0000 1111
    *****************************************************************/

    /* get instance when do not support c++11 */
    static CameraHubGWMv2* GetInstanceC98(BYTE cameraCreatFlag = 5);

    /* get instance when support c++11 */
    static CameraHubGWMv2* GetInstanceC11(BYTE cameraCreatFlag = 5);

    CameraHubGWMv2(const CameraHubGWMv2&) = delete;
    CameraHubGWMv2& operator=(const CameraHubGWMv2&) = delete;

    ~CameraHubGWMv2();

private:
    CameraHubGWMv2(BYTE cameraCreatFlag);

private:
    static mutex mMutex;
};

} // namespace Camera
} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_APROJECT_GWMV2MH_CAMERA_CAMERAHUBGWMV2_H__
