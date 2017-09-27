#include "ADASManager/AVM/AAvmBase.h"
#include "Subject.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

CAvmBase::CAvmBase()
    :Observer("AVM")
{
    m_mMapAvmFunc.clear();

}


CAvmBase::~CAvmBase()
{
    for(auto it = m_mMapAvmFunc.begin(); it != m_mMapAvmFunc.end(); ++it)
    {
        (*it).second->release();
    }
}


VOID CAvmBase::onHandle(UInt32 uiEventID, const string& pData)
{
    ALOGD("CAvmBase::onHandle\n");
    auto it= m_mMapAvmFunc.find(uiEventID);
    if( it!= m_mMapAvmFunc.end() )
    {
        CFunctor* pfunctor = (*it).second;

        (*pfunctor)(pData);
        return ;
    }
    return ;
}


a_status CAvmBase::registerFunc(UInt32 eventID, CFunctor* pFunctor)
{
   ALOGD("CAvmBase::registerFunc\n");
   m_mMapAvmFunc.insert(makePair(eventID, pFunctor));
}

a_status CAvmBase::initialize()
{
	
	ALOGD("CAvmBase::initialize \n");
	registerFunc((UInt32)eMessageType_SwitchAVM, makeFunctor(this, &CAvmBase::SwitchAVM));
}

VOID  CAvmBase::afterHandleMessageQueue()
{

}

a_status CAvmBase::isModuleAvailabel()
{
    return OK;
}

VOID CAvmBase::SwitchAVM(const string& AVMMode)
{
	ALOGD("CAvmBase::SwitchAVM  to run stateMachine AVMMode is %s \n",AVMMode.c_str());
	// To do with m_pFrontCamera...
}

VOID CAvmBase::updateModuleState()
{
	ALOGD("CAvmBase::updateModuleState \n");

}

VOID CAvmBase::Update(Subject* subject, Int32 state)
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
