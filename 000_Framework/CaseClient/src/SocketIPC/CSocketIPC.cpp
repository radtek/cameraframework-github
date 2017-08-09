#include "CSocketIPC.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace CaseClient {

#define SOKCET_IPC_ADD "127.0.0.1"
#define SOKCET_IPC_PORT 8881
CSocketIPC*  CSocketIPC::s_pInstance=NULL;

CSocketIPC* CSocketIPC::getInstance()
{
   if(s_pInstance == NULL)
   {
	   s_pInstance = new CSocketIPC();
   }
   return s_pInstance;
}


void CSocketIPC::delInstance()
{
	delete s_pInstance;
	s_pInstance = NULL;
}

CSocketIPC::~CSocketIPC()
{
	delete m_LocalIPCSocket;
	m_LocalIPCSocket = NULL;
	
	//while(!qCaseString.empty()){qCaseString.pop();};
}


CSocketIPC::CSocketIPC()
:CRunableBase(std::string("CSocketIPC"),false)
,m_LocalIPCSocket(NULL)
,m_sIP (SOKCET_IPC_ADD)
,m_iPort (SOKCET_IPC_PORT)
,m_pTestCallBackFunc(NULL)
{
	printf("CSocketIPC created : %s@%d! \n",m_sIP.c_str(),m_iPort);
}

void CSocketIPC::init()
{
	m_LocalIPCSocket = new CCommonSocket(SOKCET_IPC_ADD,SOKCET_IPC_PORT,false);
	printf("case client target is coming up ...\n");
}
//client thred
//todo: receive remote mock IPC request
//todo: monitor lock IPC thread
//todo: case client tagert online state
void CSocketIPC::update()
{
#if 1
	string sCaseStr =m_LocalIPCSocket->SocketRecv();
	if((""!=sCaseStr)&&(sCaseStr.size()>=1))
	{
		//qCaseString.push(sCaseStr);
		//just call api push, non-block function
		vRunTestFunc(sCaseStr);
	}
	#if 1
	//no case deamon detected here
	else if (!m_LocalIPCSocket->bIsConnected()) 
	{
		//block on socket reconnection
		//printf("reconnect launched! wait case client deamon coming up ...\n");
		 m_LocalIPCSocket->iTryConnect();
		usleep(10000000);
	}
	#endif
#endif
    usleep(10000);
}

void CSocketIPC::vSendStr(string str)
{
	static int ilostCnt =0;
	if(!m_LocalIPCSocket)
	{
		ilostCnt++;
		printf("case client socket is not ready[%d]: %s is not transfered...\n",ilostCnt,str.c_str());
		return;
	}
	m_LocalIPCSocket->SocketSend(str+"\n");//to seperate mul string in a msg!!
	//m_LocalIPCSocket->SocketSend(str);
}

void CSocketIPC::vRunTestFunc(string sTestStr)
{
	//printf(" case client target to test api which pair with string [%s]\n",sTestStr.c_str() );
	//adptor to GMWv2
	if(m_pTestCallBackFunc) (*m_pTestCallBackFunc) (sTestStr);
}

void CSocketIPC::vRegTestCallBack(CFunctor* pCallBack)
{
	m_pTestCallBackFunc=pCallBack;
};


} // namespace CaseClient
} // namespace AFramework
} // namespace Adas
} // namespace Harman


