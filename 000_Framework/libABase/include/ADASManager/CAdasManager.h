#ifndef _C_ADAS_MANAGER_H_
#define _C_ADAS_MANAGER_H_


#include "CMQRunnableService.h"
#include "CMessageQueue.h"
#include "CSocketIPC.h"
using namespace Harman::Adas::AFramework::CaseClient;
using Harman::Adas::AFramework::CaseClient::CSocketIPC;

//#include "IAdasCtrl.h"
using namespace Harman::Adas::AFramework::AFoundation;
using Harman::Adas::AFramework::AFoundation::CMQRunnableService;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class CAdasManager : public CMQRunnableService
{
public:
	//static CAdasManager* 	getInstance();
	//static void				deleteInstance();
	virtual ~CAdasManager();

	//bool initialize(string sServiceName);
	void init();

	// push message
	//void pushMessage(const tagBaseMessage& rMsg, UInt32 uiLen);
	//void update();
	virtual void beforeHandleMessageQueue();
	virtual void afterHandleMessageQueue();
	void vAddModule();

	CAdasManager(const string& strName, CMessageQueue* pMsgQueue);
	void vCaseCallback(const string& strMockIPC);

protected:	// data

private:	// data
	//static CAdasManager*	s_pInstance;
    //IAdasCtrl*		m_pCtrl;
};

}
}
}
}
}

#endif /* _CADAS_MANAGER_H_ */

