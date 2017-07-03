#ifndef _CASELOGCOLLECTOR_H_
#define _CASELOGCOLLECTOR_H_
#include "../../../../libAFoundation/include/AFoundation.h"
#include "../../../include/ServerSocket.h"

using namespace Harman::Adas::AFramework::AFoundation;
using Harman::Adas::AFramework::AFoundation::CRunableBase;
using namespace Harman::Adas::AFramework::CaseClient;

class CCaseLogCollector : public CRunableBase
{
public:
	static CCaseLogCollector* 	getInstance();
    static void 			delInstance();
    virtual ~CCaseLogCollector();
    void init();
    void update();
	void vSetupCollector(string sIP, int iPort);
	//void vResumeCollection();
    string sPopOneLog();
	bool bisEmpty() {return qCaseLog.empty();};
	bool bisOneCaseDone() {return m_bOneCaseFinished;};
	void vResetUsecaseProcess();

	void vSendStr(string str);//to support send api string to test target app
	void vWaitAck();// to sync between deamon and test target when run use case mode
	void vSetAck();// to sync between deamon and test target when run use case mode
private:
    CCaseLogCollector();
	static CCaseLogCollector*  s_pInstance;
	queue<string> qCaseLog;
	CCommonSocket * m_LocalIPCServSocket;	
	string m_sIP;
	int m_iPort;
	bool m_bCaseStarted;
	bool m_bOneCaseFinished;
};
#endif
