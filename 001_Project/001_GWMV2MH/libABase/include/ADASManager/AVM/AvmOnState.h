#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_AVM_ON_STATE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_AVM_ON_STATE_H__

#include "State.h"
#include "StateMachine.h"
#include "AvmEventDefine.h"

//#include <signal.h>

using namespace std;

using Harman::Adas::AFramework::AFoundation::State;
using Harman::Adas::AFramework::AFoundation::StateMachine;
using namespace Harman::Adas::AFramework::AFoundation;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class CAvmOnState : public State
{
public:
    CAvmOnState(const string& name, StateMachine* sm)
        : State(name, sm)
    {
    
    }

    VOID Enter() const;
    VOID Exit() const;

    virtual BOOLEAN ProcessMessage(UInt32 uiType, UInt32 uiID, const string& pData) const;

    ~CAvmOnState()
    {

    }

private:

};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_AVM_ON_STATE_H__
