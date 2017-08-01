
#include "ADASManager/Camera/CameraStateMachine.h"
#include "ADASManager/Camera/OffState.h"
#include "ADASManager/Camera/EnableState.h"
#include "ADASManager/Camera/DefaultState.h"
#include "ADASManager/Camera/SuspendState.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

CameraStateMachine::CameraStateMachine(const string& name, CameraDriverProviderFactory* factory)
    : StateMachine(name)
    , m_pCameraDriverProviderFactory(factory)
{
    m_pCameraDriverProvider = m_pCameraDriverProviderFactory->CreateCameraDriverProvider(name);

    //init m_mapStateMapInt
    m_mapStateMapInt[OFFCAMERASTATE] = eSVS_Camera_State_OFF;
    m_mapStateMapInt[SUSPENDCAMERASTATE] = eSVS_Camera_State_Suspend;
    m_mapStateMapInt[ENABLECAMERASTATE] = eSVS_Camera_State_Enable;

    //creat specific State belongs to CameraStateMachine
    m_pDefaultState = make_shared<DefaultState>(DEFAULTCAMERASTATE, this);
    m_pOffState = make_shared<OffState>(OFFCAMERASTATE, this);
    m_pEnableState = make_shared<EnableState>(ENABLECAMERASTATE, this);
    m_pSuspendState = make_shared<SuspendState>(SUSPENDCAMERASTATE, this);

    //add specific State to CameraStateMachine
    AddState(m_pDefaultState, nullptr);
    AddState(m_pOffState, m_pDefaultState);
    AddState(m_pEnableState, m_pDefaultState);
    AddState(m_pSuspendState, m_pDefaultState);

    /* do in child class eg:CameraStateMachineGWMv2 */
    // //set "m_pOffState" as init state of CameraStateMachine
    // SetInitialState(m_pOffState);

    /* do in child class eg:CameraStateMachineGWMv2 */
    // //start StateMachine
    // Start();
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman