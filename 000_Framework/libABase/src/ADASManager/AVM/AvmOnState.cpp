#include "ADASManager/AVM/AvmOnState.h"
#include "ADASManager/AVM/AvmStateMachine.h"
#include "MessageForQueue.h"
#include <iostream>
#include <thread>
#include <chrono>

using Harman::Adas::AFramework::AFoundation::MessageForQueue;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

VOID CAvmOnState::Enter() const
{
    ALOGI("Enter state : %s !\n", GetStateName().c_str());
}

VOID CAvmOnState::Exit() const
{
    ALOGI("Exit state : %s !\n", GetStateName().c_str());
}


BOOLEAN CAvmOnState::ProcessMessage(UInt32 uiType, UInt32 uiMessageID, const string& pData) const
{
    ALOGI("CAvmOnState::ProcessMessage : message id = %s !\n");

	CAvmStateMachine* csm;
	bool ret = false;

	switch(uiMessageID)
	{
		case 1 :

			csm = dynamic_cast<CAvmStateMachine*>(m_pStateMachine);
            if (csm != nullptr)
			{
				m_pStateMachine->TransitionTo(csm->m_pAvmOnState);

				/*To do: call engine API*/
				ALOGI("OnState : To do call engine API\n");
				
				ret = true; /*get engie API result*/
				if(ret)
				{
					ALOGI("OnState : engine API return True!\n");
					return TRUE;
				}
				else
				{
					ALOGI("OnState : engine API return False!\n");
					return FALSE;				
				}
				
            }
			else{}
			
            break;

        default:
            ALOGE("error uiMessageID unknow uiMessageID = %d!!!\n", uiMessageID);
            return FALSE;
    }
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman