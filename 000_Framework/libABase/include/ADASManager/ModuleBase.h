#ifndef MODULE_BASE_H_
#define MODULE_BASE_H_
#include "TypeDefine.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class ModuleBase
{
public:
    virtual a_status  initialize() = 0;
    virtual VOID       unInitialize() = 0;
    virtual VOID       beforeHandleMessageQueue() = 0;
    virtual VOID       afterHandleMessageQueue() = 0;
    virtual VOID       onHandle(UInt32 uiEventID, const string& pData) = 0;
    virtual a_status  isModuleAvailabel() = 0;
};

}//ADASManager
}//ABase
}//AFramework
}//Adas
}//Harman

#endif