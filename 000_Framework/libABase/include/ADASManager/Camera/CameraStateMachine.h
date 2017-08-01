#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERASTATEMACHINE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERASTATEMACHINE_H__

#include <memory>

#include "State.h"
#include "StateMachine.h"
#include "CameraEventDefine.h"
#include "CameraDriverProvider.h"
#include "CameraDriverProviderFactory.h"

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
    CameraStateMachine(const string& name, CameraDriverProviderFactory* factory);

    ~CameraStateMachine()
    {
        if(nullptr != m_pCameraDriverProvider) {
            delete m_pCameraDriverProvider;
            m_pCameraDriverProvider = nullptr;
        }

        if(nullptr != m_pCameraDriverProviderFactory) {
            delete m_pCameraDriverProviderFactory;
            m_pCameraDriverProviderFactory = nullptr;
        }
    }

public:
    //DefaultState
    shared_ptr<State> m_pDefaultState;

    //OffState
    shared_ptr<State> m_pOffState;

    //EnableState
    shared_ptr<State> m_pEnableState;

    //SuspendState
    shared_ptr<State> m_pSuspendState;

private:
    friend class OffState;
    friend class EnableState;
    friend class SuspendState;
    CameraDriverProvider* m_pCameraDriverProvider = nullptr;
    CameraDriverProviderFactory* m_pCameraDriverProviderFactory = nullptr;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERASTATEMACHINE_H__
