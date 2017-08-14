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
//using Harman::Adas::AFramework::AFoundation::tagBaseMessage;
using Harman::Adas::AProject::GWMV2MH::Camera::CameraHubGWMv2;
using Harman::Adas::AProject::GWMV2MH::Camera::CameraStateMachineGWMv2;

/*************************** test  stateMachine ************************************/
// int main(int argc, char** argv) {

//     //print platfrom category here
//     PRINT_APP_OS_TYPE;

//     cout << endl;
//     cout << endl;
//     cout << endl;

//     //new a real staemachine . eg:CameraStateMachine which extends from StateMachine(abstract class)
//     string stateMachineName{"CameraStateMachineGWMv2"};
//     shared_ptr<StateMachine> stateMachine = make_shared<CameraStateMachineGWMv2>(stateMachineName);

//     //creat a message(reverseGear) which will be sended to statemachine.  processed by statemachine or sub-clsss of State(abstract class).
//     string reverseGear{"TcuTgsLever7"};
//     shared_ptr<tagBaseMessage> reverseGearMessage = make_shared<tagBaseMessage>(7 /*reverseGear*/, 2 /*not used now*/, const_cast<char*>(reverseGear.c_str() /*not used now*/));
//     stateMachine->SendMessage(reverseGearMessage);

//     //slee 3 seconds
//     sleep(3);

//     //creat a message(parkGear) which will be sended to statemachine.  processed by statemachine or sub-clsss of State(abstract class).
//     string parkGear{"TcuTgsLever8"};
//     shared_ptr<tagBaseMessage> parkGearMessage = make_shared<tagBaseMessage>(8 /*parkGear*/, 2 /*not used now*/, const_cast<char*>(parkGear.c_str() /*not used now*/));
//     stateMachine->SendMessage(parkGearMessage);

//     sleep(1);

//     string reverseGear2{"TcuTgsLever7"};
//     shared_ptr<tagBaseMessage> reverseGearMessage2 = make_shared<tagBaseMessage>(7 /*reverseGear*/, 2 /*not used now*/, const_cast<char*>(reverseGear2.c_str() /*not used now*/));
//     stateMachine->SendMessage(reverseGearMessage2);

//     //main thread wait here
//     getchar();

//     return 0;
// }



/*************************** test  CameraHub ************************************/

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

        m_pReserveCamera->OpenCamera();
        //m_pRightCamera->OpenCamera();

        m_pReserveCamera->StartCapture();
        //m_pRightCamera->StartCapture();

        sleep(10);  //because sleep 500ms in state machine for test ,so just bigger than 500ms

        m_pReserveCamera->StopCapture();
        //m_pRightCamera->StopCapture();

        //ALOGI("FakeRVC : CloseCamera\n");
        //m_pReserveCamera->CloseCamera();
        //m_pRightCamera->CloseCamera();

        sleep(4);

        m_pReserveCamera->StartCapture();

        sleep(10);

        m_pReserveCamera->CloseCamera();
    }

    VOID Update(Subject* subject, Int32 status) {
        // if(subject->GetSubjectName().compare(FRONTCAMERANAME) == 0){
        //     ALOGI("m_CamerasState Update by : %s with state : %d !!!\n", FRONTCAMERANAME, status);
        // } else if (subject->GetSubjectName().compare(RESERVECAMERANAME) == 0){
        //     ALOGI("m_CamerasState Update by : %s with state : %d !!!\n", RESERVECAMERANAME, status);
        // } else if (subject->GetSubjectName().compare(LEFTCAMERANAME) == 0){
        //     ALOGI("m_CamerasState Update by : %s with state : %d !!!\n", LEFTCAMERANAME, status);
        // } else if (subject->GetSubjectName().compare(RIGHTCAMERANAME) == 0){
        //     ALOGI("m_CamerasState Update by : %s with state : %d !!!\n", RIGHTCAMERANAME, status);
        // } else {
        //     ALOGE("m_CamerasState Update by unknow camera with state : %d !!!\n", status);
        // }

        ALOGI("m_CamerasState Update by : %s with state : %d !!!\n", subject->GetSubjectName().c_str(), status);

        m_CamerasState[subject->GetSubjectName()] = status;
    }

    ~FakeRVC() {
        m_pHub->CancelSubscribeToReserveCamera(this);
        //m_pHub->CancelSubscribeToRightCamera(this);
    }

private:
    map<string, Int32> m_CamerasState;
    CameraHub* m_pHub;

    Camera* m_pReserveCamera;
    //Camera* m_pRightCamera;
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

    delete o;

    return 0;
}