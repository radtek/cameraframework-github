
#include "ADASManager/Camera/OffState.h"
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

VOID OffState::Enter() const
{
    ALOGI("Enter state : %s !\n", GetStateName().c_str());
}

VOID OffState::Exit() const
{
    ALOGI("Exit state : %s !\n", GetStateName().c_str());
}

VOID OffState::NotifyTimer(TimeValue v)
{
    OffState* obj = (OffState*)(v.sival_ptr);
    obj->TimerCallback();
}

VOID OffState::TimerCallback()
{
    ALOGI("%s SendMessage message id = %d !\n", GetStateName().c_str(), eCameraStateTriggerEvent_OpenCamera_REAL);
    m_pStateMachine->SendMessage(new MessageForQueue(0, eCameraStateTriggerEvent_OpenCamera_REAL, "OffState"));
}

VOID OffState::SetTimmer() const
{
    ALOGI("%s SetTimmer!\n", GetStateName().c_str());
    m_pDelayEnterReverseGearTimer->CTimer_setTime(0, HYSTERESISTIME_REVGEAR);
}

VOID OffState::ClearTimmer() const
{
    ALOGI("%s ClearTimmer!\n", GetStateName().c_str());
    m_pDelayEnterReverseGearTimer->CTimer_clear();
}

BOOLEAN OffState::ProcessMessage(UInt32 uiType, UInt32 uiMessageID, const string& pData) const
{
    ALOGI("ProcessMessage : message id = %d !\n", uiMessageID);

    switch(uiMessageID)
    {
        CameraStateMachine* csm;

        case eCameraStateTriggerEvent_OpenCamera :
            SetTimmer();
            break;

        case eCameraStateTriggerEvent_CloseCamera :
            ClearTimmer();
            break;

        case eCameraStateTriggerEvent_OpenCamera_REAL :
            ClearTimmer();
            csm = dynamic_cast<CameraStateMachine*>(m_pStateMachine);
            if (csm != nullptr) {
                Int32 ret = csm->m_pCameraDriverProvider->OpenCamera();
                if(0 == ret){
                    ALOGI("OffState OpenDriver success , TransitionTo EnableState !!!!\n");
                    m_pStateMachine->TransitionTo(csm->m_pEnableState);
                } else {
                    ALOGE("OffState OpenDriver failed , keep OffState !!!!\n");
                    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                }
            } else {
                ALOGE("error CameraStateMachine do not exit !!!!\n");
                return FALSE;
            }
            break;

        case eCameraStateTriggerEvent_CloseCamera_REAL :
            ClearTimmer();
            ALOGE("error uiMessageID = %d !!!!\n", uiMessageID);
            return FALSE;

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

const string& OffState::GetStateName() const
{
    return m_strStateName;
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman