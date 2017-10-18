#include "ADASManager/AVM/AvmStateMachine.h"
#include "ADASManager/AVM/AvmDefaultState.h"
#include "ADASManager/AVM/AvmOnState.h"
#include "ADASManager/AVM/AvmOffState.h"


namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

CAvmStateMachine::CAvmStateMachine(const string& name)
    : StateMachine(name)
{
    //init m_mapStateMapInt
    m_mapStateMapInt[AVMOFFSTATE] = e_AVM_State_OFF;
    m_mapStateMapInt[AVMONSTATE] = e_AVM_State_ON;

    //creat specific State belongs to AvmStateMachine
    m_pAvmDefaultState = make_shared<CAvmDefaultState>(AVMDEFAULTSTATE, this);
    m_pAvmOnState = make_shared<CAvmOnState>(AVMONSTATE, this);
    m_pAvmOffState = make_shared<CAvmOffState>(AVMOFFSTATE, this);
    //add specific State to AvmStateMachine
    AddState(m_pAvmDefaultState, nullptr);
    AddState(m_pAvmOnState, m_pAvmDefaultState);
    AddState(m_pAvmOffState, m_pAvmDefaultState);

    // //set "m_pOffState" as init state of AvmStateMachine
	SetInitialState(m_pAvmOffState);

    // //start StateMachine
	Start();
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman