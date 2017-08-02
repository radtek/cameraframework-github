
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
    ALOGI("%s SendMessage message : %s !\n", GetStateName().c_str(), TiggerStr(eCameraStateTriggerEvent_StartCapture).c_str());
    m_pStateMachine->SendMessage(new MessageForQueue(0, eCameraStateTriggerEvent_StartCapture, OFFCAMERASTATE));
}

VOID OffState::SetTimmer() const
{
    ALOGI("%s SetTimmer!\n", GetStateName().c_str());
    m_pStartCaptureTimer->CTimer_setTime(0, 1);
}

VOID OffState::ClearTimmer() const
{
    ALOGI("%s ClearTimmer!\n", GetStateName().c_str());
    m_pStartCaptureTimer->CTimer_clear();
}

BOOLEAN OffState::ProcessMessage(UInt32 uiType, UInt32 uiMessageID, const string& pData) const
{
    ALOGI("OffState : ProcessMessage : message id = %s !!!\n", TiggerStr(uiMessageID).c_str());

    switch(uiMessageID)
    {
        CameraStateMachine* csm;

        case eCameraStateTriggerEvent_OpenCamera :  // OpenCamera, change state from OffState to SuspendState
            csm = dynamic_cast<CameraStateMachine*>(m_pStateMachine);
            if (csm != nullptr) {
                Int32 ret = csm->m_pCameraDriverProvider->OpenCamera();
                if(0 == ret){
                    ALOGI("OffState : OpenDriver success , TransitionTo SuspendState !!!!\n");
                    m_pStateMachine->TransitionTo(csm->m_pSuspendState);
                } else {
                    ALOGE("OffState : OpenDriver failed , keep OffState !!!!\n");
                    return TRUE;
                }
            } else {
                ALOGE("OffState : error CameraStateMachine do not exit !!!!\n");
                return TRUE;
            }
            break;

        case eCameraStateTriggerEvent_CloseCamera:
            ALOGW("OffState : worning uiMessageID = %s !!! ,currentState is OffState, do not need this trigger !!!\n", TiggerStr(uiMessageID).c_str());
            return TRUE;

        case eCameraStateTriggerEvent_StartCapture:  // OpenCamera + StartCapture, change state from OffState to EnableState
            // first : OpenCamera, change state from OffState to SuspendState
            csm = dynamic_cast<CameraStateMachine*>(m_pStateMachine);
            if (csm != nullptr) {
                Int32 ret = csm->m_pCameraDriverProvider->OpenCamera();
                if(0 == ret){
                    ALOGI("OffState : OpenDriver success , TransitionTo SuspendState !!!\n");
                    m_pStateMachine->TransitionTo(csm->m_pSuspendState);
                } else {
                    ALOGE("OffState : OpenDriver failed , keep OffState !!!\n");
                    return TRUE;
                }
            } else {
                ALOGE("OffState : error CameraStateMachine do not exit !!!\n");
                return TRUE;
            }

            // second : GetCapture , change state from SuspendState to EnableState
            // when cameraStatemachine receive message: eCameraStateTriggerEvent_StartCapture, carrentState has been SuspendState
            SetTimmer();

            break;

        case eCameraStateTriggerEvent_StopCapture:
            ALOGW("OffState : worning uiMessageID = %s !!! ,currentState is OffState, do not need this trigger !!!\n", TiggerStr(uiMessageID).c_str());
            return TRUE;

        case eCameraStateTriggerEvent_StartCapture_REAL:
            ALOGW("OffState : worning uiMessageID = %s !!! ,currentState is OffState, do not need this trigger !!!\n", TiggerStr(uiMessageID).c_str());
            return TRUE;

        case eCameraStateTriggerEvent_StopCapture_REAL:
            ALOGW("OffState : worning uiMessageID = %s !!! ,currentState is OffState, do not need this trigger !!!\n", TiggerStr(uiMessageID).c_str());
            return TRUE;

        case eCameraStateTriggerEvent_INVALID:
            ALOGE("OffState : error uiMessageID = %s !!!\n", TiggerStr(uiMessageID).c_str());
            return TRUE;

        default:
            ALOGE("OffState : error uiMessageID unknow uiMessageID = %d!!!\n", uiMessageID);
            return FALSE;
    }

    return TRUE;
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman