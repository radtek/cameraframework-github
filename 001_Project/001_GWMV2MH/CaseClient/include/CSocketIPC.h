#ifndef _CSOCKETIPC_H_
#define _CSOCKETIPC_H_
//#include "../../../libAFoundation/include/AFoundation.h"
#include "AFoundation.h"
#include "CFunctor.h"

#include "ServerSocket.h"
using namespace Harman::Adas::AFramework::AFoundation;
using Harman::Adas::AFramework::AFoundation::CRunableBase;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace CaseClient {

//typedef void (*TESTCALLBACK)(string sPara);

class CSocketIPC : public CRunableBase
{
public:
	static CSocketIPC* 	getInstance();
    static void 			delInstance();
    virtual ~CSocketIPC();
    void init();
    void update();
    void vSendStr(string str);
    void vRegTestCallBack(CFunctor* pCallBack);
    CSocketIPC();
	static CSocketIPC*  s_pInstance;
	CCommonSocket * m_LocalIPCSocket;
	string m_sIP;
	int m_iPort;
	//queue<string> qCaseString;
	void vRunTestFunc(string sTestStr);
	CFunctor*  m_pTestCallBackFunc;
};
} // namespace CaseClient
} // namespace AFramework
} // namespace Adas
} // namespace Harman

//CCR: case client recode
using namespace Harman::Adas::AFramework::CaseClient;
using Harman::Adas::AFramework::CaseClient::CSocketIPC;

#define LAUNCH_CCR 		   do{ Harman::Adas::AFramework::CaseClient::CSocketIPC::getInstance()->start();}while(0);
#define REGCB_CCR(A) 		   do{ Harman::Adas::AFramework::CaseClient::CSocketIPC::getInstance()->vRegTestCallBack(A);}while(0);

#define SENDTO_CCR(A,...)       {char LogBuffer[1024];snprintf(LogBuffer,1024, A, ## __VA_ARGS__);Harman::Adas::AFramework::CaseClient:: CSocketIPC::getInstance()->vSendStr(LogBuffer);}
//TO SYNC SOKCET BASED USE CASE
#define ACKTO_CCR       {Harman::Adas::AFramework::CaseClient:: CSocketIPC::getInstance()->vSendStr("AckUseCaseRunning");}


#endif

