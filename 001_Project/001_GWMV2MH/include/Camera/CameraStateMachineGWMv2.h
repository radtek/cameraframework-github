#ifndef __HARMAN_ADAS_APROJECT_GWMV2MH_CAMERA_CAMERASTATEMACHINEGWMV2_H__
#define __HARMAN_ADAS_APROJECT_GWMV2MH_CAMERA_CAMERASTATEMACHINEGWMV2_H__

#include <memory>

#include "ADASManager/Camera/CameraStateMachine.h"

using namespace std;

using Harman::Adas::AFramework::ABase::ADASManager::CameraStateMachine;

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {
namespace Camera {

class CameraStateMachineGWMv2 : public CameraStateMachine
{
public:
    CameraStateMachineGWMv2(const string& name);

public:
    // //DefaultState
    // shared_ptr<State> m_pDefaultState;

    // //OffState
    // shared_ptr<State> m_pOffState;

    // //EnableState
    // shared_ptr<State> m_pEnableState;
};

} // namespace Camera
} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_APROJECT_GWMV2MH_CAMERA_CAMERASTATEMACHINEGWMV2_H__
