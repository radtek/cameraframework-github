#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_AVM_AVMSTATEMACHINE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_AVM_AVMSTATEMACHINE_H__

#include <memory>
#include "TraceMacros.h"
#include "TypeDefine.h"
#include "platformdef.h"

#include "State.h"
#include "StateMachine.h"
#include "AvmEventDefine.h"

using namespace std;

using Harman::Adas::AFramework::AFoundation::State;
using Harman::Adas::AFramework::AFoundation::StateMachine;
using Harman::Adas::AFramework::AFoundation::Subject;
using namespace Harman::Adas::AFramework::AFoundation;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class CAvmStateMachine : public StateMachine
{
public:
    CAvmStateMachine(const string& name);

    ~CAvmStateMachine()
    {

    }

public:
    //DefaultState
    shared_ptr<State> m_pAvmDefaultState;

    //OnState
    shared_ptr<State> m_pAvmOnState;

    //OffState
    shared_ptr<State> m_pAvmOffState;



private:
    friend class CAvmOnState;
    friend class CAvmOffState;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_AVM_AVMSTATEMACHINE_H__
