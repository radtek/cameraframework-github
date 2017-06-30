#ifndef _C_ADAS_MANAGER_GWMV2_H_
#define _C_ADAS_MANAGER_GWMV2_H_
#include "ADASManager/CAdasManager.h"

using namespace Harman::Adas::AFramework::ABase::ADASManager;

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {

class CAdasManagerGWMv2 : public CAdasManager
{
public:
    static CAdasManagerGWMv2* 	getInstance();
    static VOID				deleteInstance();
    virtual ~CAdasManagerGWMv2();

    VOID init();
	//dedicated to case client mocker
	VOID vCaseCallback(const string& strMockIPC);

protected:
    CAdasManagerGWMv2();

protected:	// data

private:	// data
    static CAdasManagerGWMv2*	s_pInstance;
    //IAdasCtrl*		m_pCtrl;
};

}
}
}
}


#endif /* _CADAS_MANAGER_H_ */

