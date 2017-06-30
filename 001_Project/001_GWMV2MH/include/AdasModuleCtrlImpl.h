#ifndef ADAS_MODULE_CTRL_IMPL_H_
#define ADAS_MODULE_CTRL_IMPL_H_

#include "ADASManager/AdasModuleCtrl.h"

using namespace Harman::Adas::AFramework::ABase::ADASManager;

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {

class AdasModuleCtrlImpl : public AdasModuleCtrl
{
public:
    static AdasModuleCtrlImpl*   getInstance();
    static VOID             deInstance();
    virtual ~AdasModuleCtrlImpl();

    a_status CreateModules(string moduleTab[], BYTE cameraFlag);
    a_status ModuleInit();

protected:
    AdasModuleCtrlImpl();

private:

    static AdasModuleCtrlImpl* m_pInstance;
};

}//GWMV2MH
}//AProject
}//Adas
}//Harman


#endif