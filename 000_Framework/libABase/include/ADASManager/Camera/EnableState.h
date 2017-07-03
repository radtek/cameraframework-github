
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
        m_pDelayExitReverseGearTimer = new CTimer(&NotifyTimer, (VOID*)this);
    }

    VOID Enter() const;
    VOID Exit() const;

    virtual BOOLEAN ProcessMessage(UInt32 uiType, UInt32 uiID, const string& pData) const;
    const string& GetStateName() const;

    ~EnableState()
    {
        if (nullptr != m_pDelayExitReverseGearTimer) {
            delete m_pDelayExitReverseGearTimer;
            m_pDelayExitReverseGearTimer = nullptr;
        }
    }

    static VOID NotifyTimer(TimeValue v);

private:
    VOID TimerCallback();
    VOID SetTimmer() const;
    VOID ClearTimmer() const;

private:
    CTimer* m_pDelayExitReverseGearTimer = nullptr;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_ENABLESTATE_H__
