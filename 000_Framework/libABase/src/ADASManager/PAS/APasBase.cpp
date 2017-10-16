
#include "Subject.h"
#include "ADASManager/PAS/APasBase.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

APasBase::APasBase(CameraHub* hub)
    : m_bPasAvailable(FALSE)
    , m_pModuleHub(hub)
    , Observer("PAS")
{
    m_mMapPasFunc.clear();
    //m_pRearCamera = (Camera*)m_pModuleHub->SubscribeToReserveCamera(this);
}

APasBase::~APasBase()
{
    for(auto it = m_mMapPasFunc.begin(); it != m_mMapPasFunc.end(); ++it)
    {
        (*it).second->release();
    }

    //m_pModuleHub->CancelSubscribeToReserveCamera(this);
}

VOID APasBase::onHandle(UInt32 uiEventID, const string& pData)
{
    ALOGD("APasBase::onHandle\n");
    auto it= m_mMapPasFunc.find(uiEventID);
    if( it!= m_mMapPasFunc.end() )
    {
        CFunctor* pfunctor = (*it).second;

        (*pfunctor)(pData);
        return ;
    }
    return ;
}

a_status APasBase::registerFunc(UInt32 eventID, CFunctor* pFunctor)
{
   ALOGD("APasBase::registerFunc\n");
   m_mMapPasFunc.insert(makePair(eventID, pFunctor));
}

a_status APasBase::initialize()
{
    //camerahub
}

VOID  APasBase::afterHandleMessageQueue()
{
}

a_status APasBase::isModuleAvailabel()
{
    return OK;
}

VOID APasBase::Update(Subject* subject, Int32 state)
{
    ALOGI("Update  | subject name[%s] state[%d]\n", subject->GetSubjectName().c_str(), state);
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman