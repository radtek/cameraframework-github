
#include "ADASManager/Camera/CameraStateMachine.h"
#include "ADASManager/Camera/OffState.h"
#include "ADASManager/Camera/EnableState.h"
#include "ADASManager/Camera/DefaultState.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

CameraStateMachine::CameraStateMachine(const string& name)
    : StateMachine(name)
{
    //init m_mapStateMapInt
    m_mapStateMapInt[OFFCAMERASTATE] = eSVS_Camera_State_OFF;
    m_mapStateMapInt[ENABLECAMERASTATE] = eSVS_Camera_State_Enable;

    //creat specific State belongs to CameraStateMachine
    m_pDefaultState = make_shared<DefaultState>(DEFAULTCAMERASTATE, this);
    m_pOffState = make_shared<OffState>(OFFCAMERASTATE, this);
    m_pEnableState = make_shared<EnableState>(ENABLECAMERASTATE, this);

    //add specific State to CameraStateMachine
    AddState(m_pDefaultState, nullptr);
    AddState(m_pOffState, m_pDefaultState);
    AddState(m_pEnableState, m_pDefaultState);

    /* do in child class eg:CameraStateMachineGWMv2 */
    // //set "m_pOffState" as init state of CameraStateMachine
    // SetInitialState(m_pOffState);

    /* do in child class eg:CameraStateMachineGWMv2 */
    // //start StateMachine
    // Start();
}

void CameraStateMachine::SetDriverProvider(CameraDriverProvider* provider)
{
    m_pCameraDriverProvider = provider;
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman