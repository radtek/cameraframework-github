
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_ADASMODULECTRL_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_ADASMODULECTRL_H__

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
    AdasModuleCtrl();
    virtual ~AdasModuleCtrl();

    a_status initialize();

protected:
    virtual VOID  _handle(UInt32 moduleType, UInt32 moduleEventID, const string& pData);

protected:
    map<UInt32, ModuleBase*> m_mModuleMap;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif  // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_ADASMODULECTRL_H__