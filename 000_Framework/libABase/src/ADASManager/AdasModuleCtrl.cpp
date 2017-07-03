#include "ADASManager/AdasModuleCtrl.h"
#include "ADASManager/RVC/ARvcBase.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

AdasModuleCtrl::~AdasModuleCtrl()
{
   ;
}

AdasModuleCtrl::AdasModuleCtrl()
{
    m_mModuleMap.clear();
}

VOID  AdasModuleCtrl::_handle(UInt32 moduleType, UInt32 moduleEventID, const string& pData)
{
    ALOGD("_handle\n");
    if(m_mModuleMap.size() > 0)
    {
        auto it= m_mModuleMap.find(moduleType);
        if( it!= m_mModuleMap.end() )
        {
            if((*it).second->isModuleAvailabel() == OK)
            {
                (*it).second->onHandle(moduleEventID, pData);

                (*it).second->afterHandleMessageQueue();
            }
        }
    }
    else{
        ALOGE("_handle failed | moduleType[%d]\n", moduleType);
        return;
    }
}

a_status AdasModuleCtrl::initialize()
{
    ALOGD("initialize\n");
    if(m_mModuleMap.size() > 0)
    {
        for(auto iter = m_mModuleMap.begin();
            iter != m_mModuleMap.end(); ++iter)
        {
            (*iter).second->initialize();
        }
    }
    else
    {
         ALOGE("initialize  failed | ModuleMap size[%d]\n", (UInt32)m_mModuleMap.size());
         return NO_INIT;
    }
    return OK;
}



}
}
}
}
}