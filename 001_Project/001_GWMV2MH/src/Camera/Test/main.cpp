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
    {
        m_pReserveCamera = m_pHub->SubscribeToReserveCamera(this);
        //m_pRightCamera = m_pHub->SubscribeToRightCamera(this);

        m_CamerasState[RESERVECAMERANAME] = m_pReserveCamera->GetCameraState();
        ALOGI("FakeRVC : init : %s with state : %d !!!\n", RESERVECAMERANAME, m_CamerasState[RESERVECAMERANAME]);
        // m_CamerasState[RIGHTCAMERANAME] = m_pRightCamera->GetCameraState();
        // ALOGI("FakeRVC : init : %s with state : %d !!!\n", RIGHTCAMERANAME, m_CamerasState[RIGHTCAMERANAME]);

        m_pEp = new EpollGPIO(string("epoll gpio"), 465, makeFunctor(this, &FakeRVC::GPIOcallback));
        m_pEp->start();
    }

    VOID Update(Subject* subject, Int32 status) {
        ALOGI("m_CamerasState Update by : %s with state : %d !!!\n", subject->GetSubjectName().c_str(), status);

        m_CamerasState[subject->GetSubjectName()] = status;
    }

    ~FakeRVC() {
        m_pHub->CancelSubscribeToReserveCamera(this);
        //m_pHub->CancelSubscribeToRightCamera(this);

        if(m_pEp != nullptr) {
            delete m_pEp;
            m_pEp = nullptr;
        }


    }

    VOID GPIOcallback(unsigned int v) {
        printf("======================================v = %u\n", v);

        // if(v == 1) {
        //     // printf("FakeRVC : OpenCamera\n");
        //     // m_pReserveCamera->OpenCamera();

        //     printf("FakeRVC : StartCapture\n");
        //     m_pReserveCamera->StartCapture();
        // } else if (v == 0) {
        //     printf("FakeRVC : StopCapture\n");
        //     m_pReserveCamera->StopCapture();

        //     // printf("FakeRVC : CloseCamera\n");
        //     // m_pReserveCamera->CloseCamera();
        // } else {
        //     printf("FakeRVC : ERROR\n");
        // }
    }

private:
    map<string, Int32> m_CamerasState;
    CameraHub* m_pHub;

    Camera* m_pReserveCamera = nullptr;
    //Camera* m_pRightCamera;

    EpollGPIO* m_pEp = nullptr;
};

int main(int argc, char** argv) {

    //print platfrom category here
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