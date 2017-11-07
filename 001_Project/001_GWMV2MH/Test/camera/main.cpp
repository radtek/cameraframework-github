#include <iostream>
#include <memory>
#include <unistd.h>

#include <map>

#include "AFoundation.h"
#include "Camera/CameraStateMachineGWMv2.h"
#include "Camera/CameraHubGWMv2.h"

using namespace std;

using Harman::Adas::AFramework::AFoundation::StateMachine;
using Harman::Adas::AFramework::AFoundation::Observer;
using Harman::Adas::AFramework::AFoundation::EpollGPIO;
using Harman::Adas::AProject::GWMV2MH::Camera::CameraHubGWMv2;
using Harman::Adas::AProject::GWMV2MH::Camera::CameraStateMachineGWMv2;

class FakeRVC : public Observer
{
public:
    FakeRVC(const string& name, CameraHub* hub)
        : Observer(name)
        , m_pHub(hub)
        , m_pEp(nullptr)
    {
        m_pReserveCamera = m_pHub->SubscribeToReserveCamera(this);

        m_CamerasState[RESERVECAMERANAME] = m_pReserveCamera->GetCameraState();
        ALOGI("FakeRVC : init : %s with state : %d !!!\n", RESERVECAMERANAME, m_CamerasState[RESERVECAMERANAME]);

        printf("FakeRVC : OpenCamera\n");
        m_pReserveCamera->OpenCamera();

        m_pEp = new EpollGPIO(string("epoll gpio"), REVERSE_GEAR_GPIO_NUM, makeFunctor(this, &FakeRVC::GPIOcallback));
        m_pEp->start();
    }

    VOID Update(Subject* subject, Int32 status) {  // called by statemachine/messageQueue Looper Thread
        ALOGI("m_CamerasState Update by : %s with state : %d !!!\n", subject->GetSubjectName().c_str(), status);

        m_CamerasState[subject->GetSubjectName()] = status;

        //tell HMI cameras state
        //.....
        //.....
        //.....
        //.....
        //.....
    }

    ~FakeRVC() {
        printf("FakeRVC : CloseCamera\n");
        m_pReserveCamera->CloseCamera();

        m_pHub->CancelSubscribeToReserveCamera(this);

        if(m_pEp != nullptr) {
            delete m_pEp;
            m_pEp = nullptr;
        }
    }

    VOID GPIOcallback(unsigned int v) { // called by GPIO epoll Thread
        printf("======================================v = %u\n", v);

        // do job : OpenCamera/StartCapture/StopCapture/CloseCamera
        if(v == REVERSE_GEAR_COME_ON) {
            printf("FakeRVC : GPIO = %u, StartCapture\n", v);
            m_pReserveCamera->StartCapture();
        } else if (v == REVERSE_GEAR_HAS_GONE) {
            printf("FakeRVC : GPIO = %u, StopCapture\n", v);
            m_pReserveCamera->StopCapture();
        } else {
            printf("FakeRVC : GPIO = %u, ERROR\n", v);
        }
    }

private:
    map<string, Int32> m_CamerasState;
    CameraHub* m_pHub = nullptr;

    Camera* m_pReserveCamera = nullptr;

    EpollGPIO* m_pEp = nullptr;
};

int main(int argc, char** argv)
{
    PRINT_APP_OS_TYPE;

    cout << endl;
    cout << endl;
    cout << endl;

    Observer* o = new FakeRVC("FakeRVC", CameraHubGWMv2::GetInstanceC11(4));

    //main thread wait here
    getchar();

    if(o != nullptr) {
        delete o;
        o = nullptr;
    }

    return 0;
}