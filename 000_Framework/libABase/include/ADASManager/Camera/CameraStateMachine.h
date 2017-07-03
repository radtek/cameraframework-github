#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERASTATEMACHINE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERASTATEMACHINE_H__

#include <memory>

#include "State.h"
#include "StateMachine.h"
#include "CameraEventDefine.h"

using namespace std;

using Harman::Adas::AFramework::AFoundation::State;
using Harman::Adas::AFramework::AFoundation::StateMachine;
using Harman::Adas::AFramework::AFoundation::Subject;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class CameraStateMachine : public StateMachine
{
public:
    CameraStateMachine(const string& name);

public:
    //DefaultState
    shared_ptr<State> m_pDefaultState;

    //OffState
    shared_ptr<State> m_pOffState;

    //EnableState
    shared_ptr<State> m_pEnableState;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERASTATEMACHINE_H__
