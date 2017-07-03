
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_OFFSTATE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_OFFSTATE_H__

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

class OffState : public State
{
public:
    OffState(const string& name, StateMachine* sm)
        : State(name, sm)
    {
        m_pDelayEnterReverseGearTimer = new CTimer(&NotifyTimer, (VOID*)this);
    }

    VOID Enter() const;
    VOID Exit() const;

    virtual BOOLEAN ProcessMessage(UInt32 uiType, UInt32 uiID, const string& pData) const;
    const string& GetStateName() const;

    ~OffState()
    {
        if (nullptr != m_pDelayEnterReverseGearTimer) {
            delete m_pDelayEnterReverseGearTimer;
            m_pDelayEnterReverseGearTimer = nullptr;
        }
    }

    static VOID NotifyTimer(TimeValue v);

private:
    VOID TimerCallback();
    VOID SetTimmer() const;
    VOID ClearTimmer() const;

private:
    CTimer* m_pDelayEnterReverseGearTimer = nullptr;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_OFFSTATE_H__