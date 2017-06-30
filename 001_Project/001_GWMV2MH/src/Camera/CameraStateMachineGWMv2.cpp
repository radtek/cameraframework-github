
#include "Camera/CameraStateMachineGWMv2.h"

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {
namespace Camera {

CameraStateMachineGWMv2::CameraStateMachineGWMv2(const string& name)
    : CameraStateMachine(name)
{
    /* do in base class CameraStateMachine */
    // //creat specific State belongs to CameraStateMachine
    // m_pDefaultState = make_shared<DefaultState>(DEFAULTCAMERASTATE, this);
    // m_pOffState = make_shared<OffState>(OFFCAMERASTATE, this);
    // m_pEnableState = make_shared<EnableState>(ENABLECAMERASTATE, this);

    // //add specific State to CameraStateMachine
    // AddState(m_pDefaultState, nullptr);
    //     AddState(m_pOffState, m_pDefaultState);
    //     AddState(m_pEnableState, m_pDefaultState);


    /* add special state about CameraStateMachineGWMv2*/
    //
    //
    //


    //set "m_pOffState" as init state of CameraStateMachine
    SetInitialState(m_pOffState);

    //start StateMachine
    Start();
}

} // namespace Camera
} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman