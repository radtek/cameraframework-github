#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_AVM_OFF_STATE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_AVM_OFF_STATE_H__

#include "State.h"
#include "StateMachine.h"
#include "AvmEventDefine.h"

using namespace std;

using Harman::Adas::AFramework::AFoundation::State;
using Harman::Adas::AFramework::AFoundation::StateMachine;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class CAvmOffState : public State
{
public:
    CAvmOffState(const string& name, StateMachine* sm)
        : State(name, sm)
    {
    
    }

    VOID Enter() const;
    VOID Exit() const;

    virtual BOOLEAN ProcessMessage(UInt32 uiType, UInt32 uiID, const string& pData) const;

    ~CAvmOffState()
    {

    }

private:

};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_AVM_OFF_STATE_H__

