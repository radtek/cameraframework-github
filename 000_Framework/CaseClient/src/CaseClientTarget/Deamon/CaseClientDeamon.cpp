#include "CaseClientDeamon.h"
#define SOCKET_RECONNECT_TIMER  10
using namespace Harman::Adas::AFramework::AFoundation;
using Harman::Adas::AFramework::AFoundation::CRunableBase;

CCaseClientDeamon*  CCaseClientDeamon::s_pInstance=NULL;

CCaseClientDeamon* CCaseClientDeamon::getInstance()
{
   if(s_pInstance == NULL)
   {
	   s_pInstance = new CCaseClientDeamon();
   }
   return s_pInstance;
}


void CCaseClientDeamon::delInstance()
{
	delete s_pInstance;
	s_pInstance = NULL;
}

CCaseClientDeamon::~CCaseClientDeamon()
{
	delete m_pAdasSocketManager;
	m_pAdasSocketManager = NULL;
	printf("CCaseClientDeamon destroyed! \n");
}

CCaseClientDeamon::CCaseClientDeamon()
:CRunableBase("CCaseClientDeamon",false)
,m_pAdasSocketManager(NULL)	
,m_sIP ("0.0.0.0")//default
,m_iPort (8888)
{

	printf("CCaseClientDeamon created! \n");
}

void CCaseClientDeamon::vSetupCaseClientDeamon(string sIP, int iPort)
{
	m_sIP = sIP;
	m_iPort = iPort;
}

void CCaseClientDeamon::init()
{
	m_pAdasSocketManager = new CAdasCaseManager(m_sIP,m_iPort);
	m_pAdasSocketManager->CAdasAcceptConnect();
}

void CCaseClientDeamon::update()
{
	static int iCntSocketNeedReConnect =0;
	static int iCntWaitOneCaseReady =0;
    string newcommand = m_pAdasSocketManager->CAdasRecvCommand();
    //test
    //while(1){sleep(10000);};
    //if it is a use case, then new command have the whole info of the use case
    //can not accept another command before it done
    if((""!=newcommand)&&(newcommand.size()>=1))
    {
		m_pAdasSocketManager->CAdasParseXML(newcommand);
		//debug dump received string to console
		//printf("%s",m_pAdasSocketManager->dumpstr().c_str());
		//loop back to client as debug purpose
		//send back is only used in callback mode - system call mode need trace client
		//SockManager->CAdasSendResult(SockManager->dumpstr().c_str());
		//sync log Collector to get target output via socket ipc before start use case
		//collector keep receiving from socket but not push the case log buffer

		//send a start tag of the use case then collector will push the text received from target
		m_pAdasSocketManager->CAdasExcuteCommand();
		//wait collector to receive the stop tag of a use case
		//todo: separate command execute part to make manager handler control command at same time
		if(!m_pAdasSocketManager->bIsSingleCommandMode())
		{
			iCntWaitOneCaseReady=0;
			//if case log not receive start tag form target
			while(!CCaseLogCollector::getInstance()->bisOneCaseDone())
			{
				iCntWaitOneCaseReady++;
				if((iCntWaitOneCaseReady>=10)&&CCaseLogCollector::getInstance()->bisEmpty())
				{
					printf("CCaseLog Collector long time not receive output in use case mode! \n");
					printf("CCaseLog Collector exit use case mode! \n");
					iCntWaitOneCaseReady=0;
					CCaseLogCollector::getInstance()->vResetUsecaseProcess();
					break;
				}
				else if((iCntWaitOneCaseReady%3)==0)
				{
					printf("CCaseLog Collector is just working, not reach the end of use case yet!! \n");
				}

				usleep(1000000);
			}
			//send result to target
			while(!CCaseLogCollector::getInstance()->bisEmpty())
			{
				m_pAdasSocketManager->CAdasSendResult(CCaseLogCollector::getInstance()->sPopOneLog()+"\n");//this return is case tool to get single msg
				usleep(10000);
			}
		}

		//send sync to lunch next case on "CaseClient on Target Board is idle"
		m_pAdasSocketManager->CAdasSendResult("CaseClient on Target Board is idle");
		
    }
    else
    {
    	iCntSocketNeedReConnect++;
    	if(SOCKET_RECONNECT_TIMER<iCntSocketNeedReConnect)
    	{
    		//block on socket reconnection
    		printf("reconnect required! CCaseClientDeamon wait case viewer coming up ...\n");
    		m_pAdasSocketManager->CAdasAcceptConnect();
    		iCntSocketNeedReConnect =0;
    	}
    	usleep(10000);
    }
}



