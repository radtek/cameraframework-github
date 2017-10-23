#include "ADASManager/AVM/AvmDefaultState.h"
#include "ADASManager/AVM/AvmStateMachine.h"
#include "TraceMacros.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

CAvmDefaultState::~CAvmDefaultState()
{}

VOID CAvmDefaultState::Enter() const
{
    ALOGI("Enter state : %s !\n", GetStateName().c_str());
}

VOID CAvmDefaultState::Exit() const
{
    ALOGI("Exit state : %s !\n", GetStateName().c_str());
}

BOOLEAN CAvmDefaultState::ProcessMessage(UInt32 uiType, UInt32 uiID, const string& pData) const
{
    ALOGI("ProcessMessage : message id = %d !\n", uiID);

	CAvmStateMachine* csm;
	bool ret = false;
	
	switch(uiID)
	{
		case 1 :

			csm = dynamic_cast<CAvmStateMachine*>(m_pStateMachine);
            if (csm != nullptr)
			{
				m_pStateMachine->TransitionTo(csm->m_pAvmDefaultState);

				/*To do: call engine API*/
				ALOGI("DefaultState : To do call engine API\n");
				
				ret = true; /*get engie API result*/
				if(ret)
				{
					ALOGI("DefaultState : engine API return True!\n");
					return TRUE;
				}
				else
				{
					ALOGI("DefaultState : engine API return False!\n");
					return FALSE;				
				}
				
            }
			else{}
			
            break;

        default:
            ALOGE("error uiMessageID unknow uiMessageID = %d!!!\n", uiID);
            return FALSE;
    }
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman