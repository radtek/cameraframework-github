#include "ADASManager/APA/AApaBase.h"
#include "Subject.h"

namespace Harman 		{
namespace Adas 			{
namespace AFramework 	{
namespace ABase 		{
namespace ADASManager 	{

AApaBase::AApaBase()
    :m_bApaAvailable(FALSE)
    ,Observer("APA")
{
    m_mMapApaFunc.clear();
}


AApaBase::~AApaBase()
{
    for(auto it = m_mMapApaFunc.begin(); it != m_mMapApaFunc.end(); ++it)
    {
        (*it).second->release();
    }
}


VOID AApaBase::onHandle(UInt32 uiEventID, const string& pData)
{
    ALOGD("AApaBase::onHandle    [%d, %s]\n", uiEventID, pData);
    auto it= m_mMapApaFunc.find(uiEventID);
    if(m_mMapApaFunc.end() != it)
    {
        CFunctor* pfunctor = (*it).second;

        (*pfunctor)(pData);
        return ;
    }
    return ;
}


a_status AApaBase::registerFunc(UInt32 eventID, CFunctor* pFunctor)
{
   ALOGD("ARvcBase::registerFunc    [%d]\n", eventID);
   m_mMapApaFunc.insert(makePair(eventID, pFunctor));
}

a_status AApaBase::initialize()
{
    //camerahub
}

VOID  AApaBase::afterHandleMessageQueue()
{

}

a_status AApaBase::isModuleAvailabel()
{
    return OK;
}

VOID AApaBase::updateModuleState()
{

}

VOID AApaBase::Update(Subject* subject, Int32 state)
{
    ALOGI("Update  | subject name[%s] state[%d]\n",  
                subject->GetSubjectName().c_str(), 
                state);
}

}//ADASManager
}//ABase
}//AFramework
}//Adas
}//Harman


