
#ifndef __HARMAN_ADAS_APROJECT_GWMV2MH_ADASMODULECTRLIMPL_H__
#define __HARMAN_ADAS_APROJECT_GWMV2MH_ADASMODULECTRLIMPL_H__

#include "ADASManager/AdasModuleCtrl.h"

using namespace Harman::Adas::AFramework::ABase::ADASManager;

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {

class AdasModuleCtrlImpl : public AdasModuleCtrl
{
public:
    static AdasModuleCtrlImpl* getInstance();
    static VOID deInstance();
    virtual ~AdasModuleCtrlImpl();

    a_status CreateModules(string moduleTab[], BYTE cameraFlag);
    a_status ModuleInit();

protected:
    AdasModuleCtrlImpl();

private:

    static AdasModuleCtrlImpl* m_pInstance;
};

} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_APROJECT_GWMV2MH_ADASMODULECTRLIMPL_H__