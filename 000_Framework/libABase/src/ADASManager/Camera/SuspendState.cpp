
#include "ADASManager/Camera/SuspendState.h"
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

VOID SuspendState::Enter() const
{
    ALOGI("Enter state : %s !\n", GetStateName().c_str());
}

VOID SuspendState::Exit() const
{
    ALOGI("Exit state : %s !\n", GetStateName().c_str());
}

VOID SuspendState::NotifyTimer(TimeValue v)
{
    SuspendState* obj = (SuspendState*)(v.sival_ptr);
    obj->TimerCallback();
}

VOID SuspendState::TimerCallback()
{
    ALOGI("%s SendMessage message : %s !\n", GetStateName().c_str(), TiggerStr(eCameraStateTriggerEvent_StartCapture_REAL).c_str());
    m_pStateMachine->SendMessage(new MessageForQueue(0, eCameraStateTriggerEvent_StartCapture_REAL, SUSPENDCAMERASTATE));
}

VOID SuspendState::SetTimmer() const
{
    ALOGI("%s SetTimmer!\n", GetStateName().c_str());
    m_pDelayEnterEnableStateTimer->CTimer_setTime(0, HYSTERESISTIME_REVGEAR);
}

VOID SuspendState::ClearTimmer() const
{
    ALOGI("%s ClearTimmer!\n", GetStateName().c_str());
    m_pDelayEnterEnableStateTimer->CTimer_clear();
}

BOOLEAN SuspendState::ProcessMessage(UInt32 uiType, UInt32 uiMessageID, const string& pData) const
{
    ALOGI("SuspendState::ProcessMessage message : %s !\n", TiggerStr(uiMessageID).c_str());

    switch(uiMessageID)
    {
        CameraStateMachine* csm;

        case eCameraStateTriggerEvent_OpenCamera :
            ALOGW("SuspendState::ProcessMessage worning uiMessageID = %s , already OpenCamera !!!!\n", TiggerStr(uiMessageID).c_str());
            return TRUE;

        case eCameraStateTriggerEvent_CloseCamera:
            ClearTimmer();
            csm = dynamic_cast<CameraStateMachine*>(m_pStateMachine);
            if (csm != nullptr) {
                Int32 ret = csm->m_pCameraDriverProvider->CloseCamera();
                if(0 == ret){
                    ALOGI("SuspendState CloseDriver success , TransitionTo OffState !!!!\n");
                    m_pStateMachine->TransitionTo(csm->m_pOffState);
                } else {
                    ALOGE("SuspendState CloseDriver failed , keep SuspendState !!!!\n");
                    m_pStateMachine->TransitionTo(csm->m_pErrorState);
                    return TRUE;
                }
            } else {
                ALOGE("SuspendState error CameraStateMachine do not exit !!!!\n");
                return TRUE;
            }
            break;

        case eCameraStateTriggerEvent_StartCapture:
            SetTimmer();
            break;

        case eCameraStateTriggerEvent_StopCapture:
            ClearTimmer();
            ALOGE("SuspendState error uiMessageID = %s !!!!\n", TiggerStr(uiMessageID).c_str());
            return TRUE;

        case eCameraStateTriggerEvent_StartCapture_REAL:
            csm = dynamic_cast<CameraStateMachine*>(m_pStateMachine);
            if (csm != nullptr) {
                Int32 ret = csm->m_pCameraDriverProvider->GetCapture();
                if(0 == ret){
                    ALOGI("SuspendState Getcapture success , TransitionTo EnableState !!!!\n");
                    m_pStateMachine->TransitionTo(csm->m_pEnableState);
                } else {
                    ALOGE("SuspendState Getcapture failed , keep SuspendState !!!!\n");
                    m_pStateMachine->TransitionTo(csm->m_pErrorState);
                    return TRUE;
                }
            } else {
                ALOGE("SuspendState error CameraStateMachine do not exit !!!!\n");
                return TRUE;
            }
            break;

        case eCameraStateTriggerEvent_StopCapture_REAL:
            ALOGE("SuspendState error uiMessageID = %s !!!!\n", TiggerStr(uiMessageID).c_str());
            return TRUE;

        case eCameraStateTriggerEvent_INVALID:
            ALOGE("SuspendState : error uiMessageID = %s !!!\n", TiggerStr(uiMessageID).c_str());
            return TRUE;

        default:
            ALOGE("SuspendState : error uiMessageID unknow uiMessageID = %d!!!\n", uiMessageID);
            return FALSE;
    }

    return TRUE;
}

// const string& SuspendState::GetStateName() const
// {
//     return m_strStateName;
// }

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman