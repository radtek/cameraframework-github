#ifndef ADAS_MODULE_CTRL_H_
#define ADAS_MODULE_CTRL_H_

#include "CMessageHandler.h"
#include "ADASManager/ModuleBase.h"

using namespace Harman::Adas::AFramework::AFoundation;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class AdasModuleCtrl : public CMessageHandler
{
public:
    enum eModuleType
    {
        eModuleType_RVC,
        eModuleType_SVC,
        eModuleType_AVM,
        eModuleType_PAS,
        eModuleType_APA,
        eModuleType_COMMON,

        eModuleType_UNKNOWN = 0x70000000
    };

public:
    AdasModuleCtrl();
    virtual ~AdasModuleCtrl();
    
    a_status initialize();

protected:
    virtual VOID  _handle(UInt32 moduleType, UInt32 moduleEventID, const string& pData);

protected:
    map<UInt32, ModuleBase*> m_mModuleMap;

};



}
}
}
}
}







#endif