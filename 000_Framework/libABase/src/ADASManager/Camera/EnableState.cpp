
#include "ADASManager/Camera/EnableState.h"
#include "ADASManager/Camera/CameraStateMachine.h"
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

VOID EnableState::Enter() const
{
    ALOGI("Enter state : %s !\n", GetStateName().c_str());
}

VOID EnableState::Exit() const
{
    ALOGI("Exit state : %s !\n", GetStateName().c_str());
}

VOID EnableState::NotifyTimer(TimeValue v)
{
    EnableState* obj = (EnableState*)(v.sival_ptr);
    obj->TimerCallback();
}

VOID EnableState::TimerCallback()
{
    ALOGI("%s SendMessage message id = %d !\n", GetStateName().c_str(), eCameraStateTriggerEvent_CloseCamera_REAL);
    m_pStateMachine->SendMessage(new MessageForQueue(0, eCameraStateTriggerEvent_CloseCamera_REAL, "EnableState"));
}

VOID EnableState::SetTimmer() const
{
    ALOGI("%s SetTimmer!\n", GetStateName().c_str());
    m_pDelayExitReverseGearTimer->CTimer_setTime(0, HYSTERESISTIME_REVGEAR);
}

VOID EnableState::ClearTimmer() const
{
    ALOGI("%s ClearTimmer!\n", GetStateName().c_str());
    m_pDelayExitReverseGearTimer->CTimer_clear();
}

BOOLEAN EnableState::ProcessMessage(UInt32 uiType, UInt32 uiMessageID, const string& pData) const
{
    ALOGI("ProcessMessage : message id = %d !\n", uiMessageID);

    switch(uiMessageID)
    {
        CameraStateMachine* csm;

        case eCameraStateTriggerEvent_CloseCamera :
            SetTimmer();
            break;

        case eCameraStateTriggerEvent_OpenCamera :
            ClearTimmer();
            break;

        case eCameraStateTriggerEvent_OpenCamera_REAL :
            ClearTimmer();
            ALOGE("error uiMessageID = %d !!!!\n", uiMessageID);
            return FALSE;

        case eCameraStateTriggerEvent_CloseCamera_REAL :
            ClearTimmer();
            csm = dynamic_cast<CameraStateMachine*>(m_pStateMachine);
            if (csm != nullptr) {
                Int32 ret = csm->m_pCameraDriverProvider->CloseCamera();
                if(0 == ret){
                    ALOGI("EnableState CloseCamera success , TransitionTo OffState !!!!\n");
                    m_pStateMachine->TransitionTo(csm->m_pOffState);
                } else {
                    ALOGE("EnableState CloseCamera failed , keep EnableState !!!!\n");
                    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                }
            } else {
                ALOGE("error statemachine do not exit !!!!\n");
                return FALSE;
            }
            break;

        case eCameraStateTriggerEvent_INVALID :
            ClearTimmer();
            ALOGE("error uiMessageID = %d !!!!\n", uiMessageID);
            return FALSE;

        default:
            ClearTimmer();
            ALOGE("error uiMessageID unknow !!!!\n");
            return FALSE;
    }
    return TRUE;
}

const string& EnableState::GetStateName() const
{
    return m_strStateName;
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman