#ifndef  A_RVC_BASE_H_
#define A_RVC_BASE_H_

#include "TraceMacros.h"
#include "TypeDefine.h"
#include "platformdef.h"
#include "CFunctor.h"
#include "ADASManager/ModuleBase.h"
#include "Observer.h"
#include "ADASManager/Camera/ReserveCamera.h"
#include "ADASManager/Camera/CameraHub.h"

using namespace std;
using namespace Harman::Adas::AFramework::AFoundation;
using Harman::Adas::AFramework::ABase::ADASManager::CameraHub;
using Harman::Adas::AFramework::ABase::ADASManager::ReserveCamera;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class ARvcBase : public ModuleBase
                            , Observer
{

public:
    enum eCamState
    {
        CAM_OFF,
        CAM_HOLD,
        CAM_ON,
        CAM_ERROR
    };

public:
    ARvcBase(CameraHub* hub);
    virtual ~ARvcBase();

public:
    virtual a_status  initialize();
    virtual VOID       unInitialize(){};
    virtual VOID       beforeHandleMessageQueue(){};
    virtual VOID       afterHandleMessageQueue();
    virtual a_status  isModuleAvailabel();
              virtual VOID Update(Subject* subject, Int32 state);
              virtual VOID onHandle(UInt32 uiEventID, const string& pData);

private:
    // typedef CFunctorArg1<const string&>  CFunctor;

protected:
    a_status registerFunc(UInt32 eventID, CFunctor* pFunctor);
              VOID  updateModuleState();

              Camera* m_pRearCamera;

    eCamState camState;


private:
    map<UInt32, CFunctor*> m_mMapRvcFunc;

    BOOLEAN m_bRvcAvailable;
              CameraHub* m_pModuleHub;




};


}//ADASManager
}//ABase
}//AFramework
}//Adas
}//Harmane


#endif