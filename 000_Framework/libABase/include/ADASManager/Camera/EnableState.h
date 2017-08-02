
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_ENABLESTATE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_ENABLESTATE_H__

#include "State.h"
#include "StateMachine.h"
#include "CameraEventDefine.h"
#include "CTimer.h"

#include <signal.h>

using namespace std;

using Harman::Adas::AFramework::AFoundation::State;
using Harman::Adas::AFramework::AFoundation::StateMachine;
using Harman::Adas::AFramework::AFoundation::CTimer;

typedef union sigval TimeValue;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class EnableState : public State
{
public:
    EnableState(const string& name, StateMachine* sm)
        : State(name, sm)
    {
        m_pDelayEnterSuspendStateTimer = new CTimer(&NotifyTimerDelayEnterSuspendState, (VOID*)this);
        m_pCloseCameraTimer = new CTimer(&NotifyTimerCloseCamera, (VOID*)this);
    }

    VOID Enter() const;
    VOID Exit() const;

    virtual BOOLEAN ProcessMessage(UInt32 uiType, UInt32 uiID, const string& pData) const;

    ~EnableState()
    {
        if (nullptr != m_pDelayEnterSuspendStateTimer) {
            delete m_pDelayEnterSuspendStateTimer;
            m_pDelayEnterSuspendStateTimer = nullptr;
        }
        if (nullptr != m_pCloseCameraTimer) {
            delete m_pCloseCameraTimer;
            m_pCloseCameraTimer = nullptr;
        }
    }

    static VOID NotifyTimerDelayEnterSuspendState(TimeValue v);
    static VOID NotifyTimerCloseCamera(TimeValue v);

private:
    VOID TimerCallbackDelayEnterSuspendState();
    VOID SetTimmerDelayEnterSuspendState() const;
    VOID ClearTimmerDelayEnterSuspendState() const;

    VOID TimerCallbackCloseCamera();
    VOID SetTimmerCloseCamera() const;
    VOID ClearTimmerCloseCamera() const;

private:
    CTimer* m_pCloseCameraTimer = nullptr;
    CTimer* m_pDelayEnterSuspendStateTimer = nullptr;

    mutable BOOLEAN m_bTimerOn = FALSE;
    mutable BOOLEAN m_bCloseCameraPurpose = FALSE;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_ENABLESTATE_H__
