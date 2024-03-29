#include "ADASManager/RVC/ARvcBase.h"
#include "Subject.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

ARvcBase::ARvcBase(CameraHub* hub)
    : m_bRvcAvailable(FALSE)
    , m_pModuleHub(hub)
    , Observer("RVC")
{
    m_mMapRvcFunc.clear();
    m_pRearCamera = (Camera*)m_pModuleHub->SubscribeToReserveCamera(this);
}


ARvcBase::~ARvcBase()
{
    for(auto it = m_mMapRvcFunc.begin(); it != m_mMapRvcFunc.end(); ++it)
    {
        (*it).second->release();
    }

    m_pModuleHub->CancelSubscribeToReserveCamera(this);
}


VOID ARvcBase::onHandle(UInt32 uiEventID, const string& pData)
{
    ALOGD("ARvcBase::onHandle\n");
    auto it= m_mMapRvcFunc.find(uiEventID);
    if( it!= m_mMapRvcFunc.end() )
    {
        CFunctor* pfunctor = (*it).second;

        (*pfunctor)(pData);
        return ;
    }
    return ;
}


a_status ARvcBase::registerFunc(UInt32 eventID, CFunctor* pFunctor)
{
    ALOGD("ARvcBase::registerFunc\n");
    m_mMapRvcFunc.insert(makePair(eventID, pFunctor));
}

a_status ARvcBase::initialize()
{
    //camerahub
}

VOID  ARvcBase::afterHandleMessageQueue()
{
}

a_status ARvcBase::isModuleAvailabel()
{
    return OK;
}

VOID ARvcBase::updateModuleState()
{
}

VOID ARvcBase::Update(Subject* subject, Int32 state)
{
    ALOGI("Update  | subject name[%s] state[%d]\n",
                subject->GetSubjectName().c_str(),
                state);
    switch(state)
    {
        case 0:
            camState = CAM_OFF;
        break;
        case 1:
            camState = CAM_HOLD;
        break;
        case 2:
            camState = CAM_ON;
        break;
        case 3:
            camState = CAM_ERROR;
        break;
    }
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman
