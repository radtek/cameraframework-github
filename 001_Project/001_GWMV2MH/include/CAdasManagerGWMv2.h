
#ifndef __HARMAN_ADAS_APROJECT_GWMV2MH_CADASMANAGERGWMV2_H__
#define __HARMAN_ADAS_APROJECT_GWMV2MH_CADASMANAGERGWMV2_H__

#include "ADASManager/CAdasManager.h"

using namespace Harman::Adas::AFramework::ABase::ADASManager;

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {

class CAdasManagerGWMv2 : public CAdasManager
{
public:
    static CAdasManagerGWMv2* getInstance();
    static VOID deleteInstance();
    virtual ~CAdasManagerGWMv2();

    VOID init();
	//dedicated to case client mocker
    VOID vCaseCallbackGWMv2(const string& strMockIPC);

protected:
    CAdasManagerGWMv2();

private:
    static CAdasManagerGWMv2* s_pInstance;
};

} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_APROJECT_GWMV2MH_CADASMANAGERGWMV2_H__