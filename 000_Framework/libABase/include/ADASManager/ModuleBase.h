#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_MODULEBASE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_MODULEBASE_H__
#include "TypeDefine.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class ModuleBase
{
public:
    virtual ~ModuleBase() {}
    virtual a_status  initialize() = 0;
    virtual VOID       unInitialize() = 0;
    virtual VOID       beforeHandleMessageQueue() = 0;
    virtual VOID       afterHandleMessageQueue() = 0;
    virtual VOID       onHandle(UInt32 uiEventID, const string& pData) = 0;
    virtual a_status  isModuleAvailabel() = 0;
};

} //namespace ADASManager
} //namespace ABase
} //namespace AFramework
} //namespace Adas
} //namespace Harman

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_MODULEBASE_H__