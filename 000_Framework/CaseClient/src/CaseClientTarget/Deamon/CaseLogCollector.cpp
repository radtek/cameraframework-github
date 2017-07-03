#include "CaseLogCollector.h"
CCaseLogCollector*  CCaseLogCollector::s_pInstance=NULL;

CCaseLogCollector* CCaseLogCollector::getInstance()
{
   if(s_pInstance == NULL)
   {
	   s_pInstance = new CCaseLogCollector();
   }
   return s_pInstance;
}


void CCaseLogCollector::delInstance()
{
	delete s_pInstance;
	s_pInstance = NULL;
}

CCaseLogCollector::~CCaseLogCollector()
{
	while(!qCaseLog.empty()){qCaseLog.pop();};
    delete m_LocalIPCServSocket;
	m_LocalIPCServSocket = NULL;	
}


CCaseLogCollector::CCaseLogCollector()
:CRunableBase("CCaseLogCollector",false)
,m_LocalIPCServSocket(NULL)	
,m_sIP ("127.0.0.1")
,m_iPort (8889)	
,m_bCaseStarted(false)
,m_bOneCaseFinished(false)
{
	while(!qCaseLog.empty()){qCaseLog.pop();};
	printf("CCaseLogCollector created! \n");
}


string CCaseLogCollector::sPopOneLog()
{
	string tmp = "CCaseLogCollector empty";
	if(!qCaseLog.empty())
	{
		tmp= qCaseLog.front();
		qCaseLog.pop();
	}
	 return tmp;
}

void CCaseLogCollector::vSetupCollector(string sIP, int iPort)
{
	m_sIP = sIP;
	m_iPort = iPort;
}
#if 0
void CCaseLogCollector::vResumeCollection()
{
	if(!qCaseLog.empty()) printf("CCaseLogCollector is not empty on resume request!!\n");
	resume();
}
#endif
void CCaseLogCollector::init()
{
	m_LocalIPCServSocket = new CCommonSocket(m_sIP.c_str(),m_iPort,true);
	m_LocalIPCServSocket->acceptConnect();
}
//sync with case client to collect use case related logs only
#define DEBUG_CASEVIEWER_START_TAG "autoTestInfo::START_OF_USE_LOG_TAG"
#define DEBUG_CASEVIEWER_END_TAG   "autoTestInfo::END_OF_USE_LOG_TAG"
//#define CASECLIENT_TARGET_START_TAG "START_OF_USE_LOG_TAG"
#define CASECLIENT_TARGET_START_TAG "CaseName:"
#define CASECLIENT_TARGET_END_TAG   "END_OF_USE_LOG_TAG"
#define CASECLIENT_TARGET_ACK_TAG   "AckUseCaseRunning"
static bool g_bNeedAck = false;

//current restriction is logs coming up slowly, we receive one string one time --> idetify mul strings by "/n" added by IPC sender
//work around , and ack tag to wait for test side correctly received case names....is that necessary? 
void CCaseLogCollector::update()
{
	string sCaseLog =m_LocalIPCServSocket->SocketRecv();
	string sCaseSingleString("CaseSingleString");
	int iPos =0;
    	//debug
    	printf("CCaseLogCollector received from target: \n***********************\n%s\n***********************\n",sCaseLog.c_str());
    if(!((""!=sCaseLog)&&(sCaseLog.size()>=1)))
    {
	//block on socket reconnection
	printf("reconnect launched! CCaseLogCollector wait target case client coming up ...\n");
	m_LocalIPCServSocket->acceptConnect();
	usleep(100000);
	return;
    }	
    while((""!=sCaseLog)&&(sCaseLog.size()>=1))
    {
    	string sTag;    	
	string sStartTag(CASECLIENT_TARGET_START_TAG);
    	string sEndTag(CASECLIENT_TARGET_END_TAG);
	string sAckTag(CASECLIENT_TARGET_ACK_TAG);

	//find first single messge from the socket package
	if ((iPos=sCaseLog.find("\n",iPos))!=string::npos)
	{
		sCaseSingleString=sCaseLog.substr(0,iPos); 
		sCaseLog = sCaseLog.substr(iPos+1);
		printf("CCaseLogCollector single string: [%s]\n",sCaseSingleString.c_str());
		printf("CCaseLogCollector new log string: [%s]\n",sCaseLog.c_str());
	}
	//in case sync block is missed 
	else if(sCaseLog.size()>=1)
	{
		sTag= sCaseLog.substr(0,(int)sAckTag.size());
		sCaseLog = sCaseLog.substr(iPos+1);
		if(CASECLIENT_TARGET_ACK_TAG==sTag)
		{
			g_bNeedAck= false;
			break;
		}

	}	
	else
	{
		printf("break: CCaseLogCollector not find single string : [%s]\n",sCaseLog.c_str());
		while(!qCaseLog.empty()){qCaseLog.pop();};
		break;
	}
	
    	sTag= sCaseSingleString.substr(0,(int)sAckTag.size());
	if(CASECLIENT_TARGET_ACK_TAG==sTag)
	{
		g_bNeedAck= false;
		continue;
	}
	
    	//*TagSTART_OF_USE_LOG_TAG should be at the beginning of the use case including input expect items
    	//if(("*TagCaseName:"==sCaseLog)&&(!bCaseStarted))
    	


    	//todo parse logs from socket....
    	//serach start
    	if(!m_bCaseStarted)
	{
		sTag= sCaseSingleString.substr(0,(int)sStartTag.size());
	}
    	else
    	{
    		;//sTag= sCaseLog.substr(0,(int)sEndTag.size());
    	}
    	//printf("CCaseLogCollector find tag from target: \n %s \n",sTag.c_str());

    	if((CASECLIENT_TARGET_START_TAG==sTag)&&(!m_bCaseStarted))
    	{
    		m_bCaseStarted = true;
    		m_bOneCaseFinished = false;
    		printf("CCaseLogCollector found a case start tag :\n===============\n%s\n===============\n",sCaseSingleString.c_str());
    		if(!qCaseLog.empty()) printf("CCaseLogCollector not empty before receive a new use case, clear it now!! \n");
    		while(!qCaseLog.empty()){qCaseLog.pop();};
    	}
    	//else if((CASECLIENT_TARGET_END_TAG==sTag))//todo maybe create empty use case
    	else if((string::npos!=sCaseSingleString.find(CASECLIENT_TARGET_END_TAG)))
    	{
    		m_bCaseStarted = false;
    		m_bOneCaseFinished = true;
    		printf("CCaseLogCollector found a case end tag!\n");
    	}
    	else if(m_bCaseStarted)
    	{
    		//use case collection is not done
    		;
    	}
    	else
    	{
    		return;
    	}
	
    	qCaseLog.push(sCaseSingleString);
    }
}

void CCaseLogCollector::vResetUsecaseProcess()
{
	m_bCaseStarted = false;
	m_bOneCaseFinished = false;
	while(!qCaseLog.empty()){qCaseLog.pop();};
	printf("CCaseLogCollector vResetUsecaseProcess done! \n");
}

void CCaseLogCollector::vSendStr(string str)
{
	static int ilostCnt =0;
	if(!m_LocalIPCServSocket)
	{
		ilostCnt++;
		printf("case client socket is not ready[%d]: %s is not transfered...\n",ilostCnt,str.c_str());
		return;
	}
	//m_LocalIPCServSocket->SocketSend(str+"\n");
	m_LocalIPCServSocket->SocketSend(str);
}

void CCaseLogCollector::vWaitAck()
{
	while(g_bNeedAck){usleep(100000);}
}


void CCaseLogCollector::vSetAck()
{
	g_bNeedAck = true;
}




