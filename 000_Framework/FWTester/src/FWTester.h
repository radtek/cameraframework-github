#ifndef _FWTESTER_H_
#define _FWTESTER_H_

#include "ABase.h"

using namespace Harman::Adas::AFramework::ABase::ADASManager;


namespace Harman {
namespace Adas {
namespace AFramework {
namespace FWTester {
	
class FWTesterModuleCtrl : public AdasModuleCtrl
{
public :
	 a_status CreateModules(UInt32 uiModuleType, ModuleBase* pBaseModule);
};

class FWTester: public CAdasManager
{
public:
    static FWTester* 	getInstance();
    static VOID		deleteInstance();
    virtual ~FWTester();

    VOID init();
	//dedicated to case client mocker
    VOID vCaseCallbackFWTester(const string& strMockIPC);

protected:	// data

private:	// data
    	FWTester();
	static FWTester*	s_pInstance;
	FWTesterModuleCtrl*  m_pTestModuleCtrl;
	CameraHub* m_pTestCameraHub;
	ARvcBase* m_pTestARvcBase;
	
    //IAdasCtrl*		m_pCtrl;
};


}
}
}
}


#endif /* _FWTESTER_H_ */

