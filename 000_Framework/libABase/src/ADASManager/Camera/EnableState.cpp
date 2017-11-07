
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

//******************m_pCloseCameraTimer****************************
VOID EnableState::NotifyTimerCloseCamera(TimeValue v)
{
    EnableState* obj = (EnableState*)(v.sival_ptr);
    obj->TimerCallbackCloseCamera();
}

VOID EnableState::TimerCallbackCloseCamera()
{
    ALOGI("%s TimerCallbackCloseCamera!\n", GetStateName().c_str());
    m_pStateMachine->SendMessage(new MessageForQueue(0, eCameraStateTriggerEvent_CloseCamera, ENABLECAMERASTATE));
}

VOID EnableState::SetTimmerCloseCamera() const
{
    ALOGI("%s SetTimmerCloseCamera!\n", GetStateName().c_str());
    m_pCloseCameraTimer->CTimer_setTime(0, 1);
}

VOID EnableState::ClearTimmerCloseCamera() const
{
    ALOGI("%s ClearTimmerCloseCamera!\n", GetStateName().c_str());
    m_pCloseCameraTimer->CTimer_clear();
}

//******************m_pDelayEnterSuspendStateTimer****************
VOID EnableState::NotifyTimerDelayEnterSuspendState(TimeValue v)
{
    EnableState* obj = (EnableState*)(v.sival_ptr);
    obj->TimerCallbackDelayEnterSuspendState();
}

VOID EnableState::TimerCallbackDelayEnterSuspendState()
{
    ALOGI("%s TimerCallbackDelayEnterSuspendState!\n", GetStateName().c_str());
    m_bTimerOn = FALSE;
    m_pStateMachine->SendMessage(new MessageForQueue(0, eCameraStateTriggerEvent_StopCapture_REAL, ENABLECAMERASTATE));
}

VOID EnableState::SetTimmerDelayEnterSuspendState() const
{
    ALOGI("%s SetTimmerDelayEnterSuspendState!\n", GetStateName().c_str());
    m_bTimerOn = TRUE;
    m_pDelayEnterSuspendStateTimer->CTimer_setTime(0, HYSTERESISTIME_REVGEAR);
}

VOID EnableState::ClearTimmerDelayEnterSuspendState() const
{
    ALOGI("%s ClearTimmerDelayEnterSuspendState!\n", GetStateName().c_str());
    m_bTimerOn = FALSE;
    m_pDelayEnterSuspendStateTimer->CTimer_clear();
}

BOOLEAN EnableState::ProcessMessage(UInt32 uiType, UInt32 uiMessageID, const string& pData) const
{
    ALOGI("EnableState::ProcessMessage : message id = %s !\n", TiggerStr(uiMessageID).c_str());

    switch(uiMessageID)
    {
        CameraStateMachine* csm;

        case eCameraStateTriggerEvent_OpenCamera :
            ALOGW("EnableState::ProcessMessage worning uiMessageID = %s , already OpenCamera !!!!\n", TiggerStr(uiMessageID).c_str());
            return TRUE;

        case eCameraStateTriggerEvent_CloseCamera:
            if(!m_bTimerOn) SetTimmerDelayEnterSuspendState();
            m_bCloseCameraPurpose = TRUE;
            break;

        case eCameraStateTriggerEvent_StopCapture:
            if(!m_bTimerOn) SetTimmerDelayEnterSuspendState();
            break;

        case eCameraStateTriggerEvent_StartCapture:
            ClearTimmerDelayEnterSuspendState();
            ALOGW("EnableState::ProcessMessage worning uiMessageID = %s , already StartCapture !!!!\n", TiggerStr(uiMessageID).c_str());
            return TRUE;

        case eCameraStateTriggerEvent_StartCapture_REAL:
            ALOGE("EnableState error uiMessageID = %s !!!!\n", TiggerStr(uiMessageID).c_str());
            return TRUE;

        case eCameraStateTriggerEvent_StopCapture_REAL:
            csm = dynamic_cast<CameraStateMachine*>(m_pStateMachine);
            if (csm != nullptr) {
                Int32 ret = csm->m_pCameraDriverProvider->StopCapture();
                if(0 == ret){
                    ALOGI("SuspendState StopCapture success , TransitionTo SuspendState !!!!\n");
                    m_pStateMachine->TransitionTo(csm->m_pSuspendState);
                } else {
                    ALOGE("SuspendState StopCapture failed , keep EnableState !!!!\n");
                    m_pStateMachine->TransitionTo(csm->m_pErrorState);
                    return TRUE;
                }
            } else {
                ALOGE("error CameraStateMachine do not exit !!!!\n");
                m_pStateMachine->TransitionTo(csm->m_pErrorState);
                return TRUE;
            }

            ALOGI("m_bCloseCameraPurpose = %d\n", m_bCloseCameraPurpose);
            if(m_bCloseCameraPurpose) {
                SetTimmerCloseCamera();
                m_bCloseCameraPurpose = FALSE;
            }

            break;

        case eCameraStateTriggerEvent_INVALID:
            ALOGE("SuspendState : error uiMessageID = %s !!!\n", TiggerStr(uiMessageID).c_str());
            return TRUE;

        default:
            ALOGE("SuspendState : error uiMessageID unknow uiMessageID = %d!!!\n", uiMessageID);
            return FALSE;
    }
    return TRUE;
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman