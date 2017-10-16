
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_ADASMODULECTRL_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_ADASMODULECTRL_H__

#include "CMessageHandler.h"
#include "ADASManager/ModuleBase.h"

using namespace Harman::Adas::AFramework::AFoundation;

#define ADAS_MODULE_RVC     string("RVC")
#define ADAS_MODULE_AVM     string("AVM")
#define ADAS_MODULE_PAS     string("PAS")
#define ADAS_MODULE_APA     string("APA")
#define ADAS_MODULE_SVC     string("SVC")
#define ADAS_MODULE_COMMON  string("COMMON")

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

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif  // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_ADASMODULECTRL_H__