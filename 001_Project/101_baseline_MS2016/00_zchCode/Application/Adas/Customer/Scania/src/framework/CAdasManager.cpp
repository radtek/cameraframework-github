#include "CAdasManager.h"
#include "CSvcIpcServiceAdaptor.h"

CAdasManager* CAdasManager::s_pInstance = NULL;

CAdasManager* CAdasManager::getInstance()
{
	if( s_pInstance == NULL)
	{
		s_pInstance = new CAdasManager();
	}

	return s_pInstance;
}

void CAdasManager::deleteInstance()
{
	if( s_pInstance != NULL )
	{
		delete s_pInstance;
		s_pInstance = NULL;
	}
}

CAdasManager::CAdasManager()
: m_pMsgQueue(NULL)
, m_pCtrl(NULL)
, m_event(TRUE)
, m_bQuit(FALSE)
{
	;
}

CAdasManager::~CAdasManager()
{
	if( m_pMsgQueue )
	{
		m_pMsgQueue->release();
	}
}
TRC_SCOPE_DEF(ADAS, CAdasManager, run);
void CAdasManager::run()
{
    TRC_SCOPE(ADAS, CAdasManager, run);
	DBG_MSG(("CAdasManager thread start working  ...\n"));
	if( m_pMsgQueue == NULL || m_pCtrl == NULL )
		return;

#ifdef PLATFORM_QNX
	pthread_setname_np(pthread_self(), "ADASManager");
#endif

	DBG_MSG(("m_pCtrl::initialize()\n"));
	if ( !m_pCtrl->initialize() )
	{
		DBG_MSG(("ADASctrl initialize failed  ...\n"));
		return;
	}

	if( m_pCtrl->isNeedFastADAS() )
	{
		m_pCtrl->startFastADAS();
		usleep(300);
	}
	else
	{
		m_pCtrl->startNormalADAS();
	}
	DBG_MSG(("CSvcIpcServiceAdaptor::connectDBus()\n"));
	// may need to start a thread to initialize svcipc
	CSvcIpcServiceAdaptor::getInstance()->connectDBus();

   //check system event which from dbus after startup
   m_pCtrl->checkSystemEventAfterStartUp();
   
	DBG_MSG(("while\n"));
	while(!m_bQuit )
	{
		m_event.wait();
		m_pCtrl->beforeHandleMessageQueue();

		//DBG_MSG(("m_pMsgQueue::handleMessageQueue\n"));
		m_pMsgQueue->handleMessageQueue();

		m_pCtrl->afterHandleMessageQueue();

		usleep(10000);
	}

	//DBG_MSG(("CSvcIpcServiceAdaptor::disConnectDBus\n"));
	//CSvcIpcServiceAdaptor::getInstance()->disConnectDBus();

	DBG_MSG(("m_pCtrl::unInitialize\n"));
	m_pCtrl->unInitialize();

	CSvcIpcServiceAdaptor::deleteInstance();

	DBG_MSG(("CAdasManager thread exit  ...\n"));

	return;
}

void CAdasManager::start(CMessageQueue* pMsgQueue, IAdasCtrl* pCtrl)
{
	if( pMsgQueue == NULL || pCtrl == NULL )
		return;

	m_pMsgQueue = pMsgQueue;
	m_pCtrl = pCtrl;

	m_hThread.start(*this);
}

TRC_SCOPE_DEF(ADAS, CAdasManager, quit);
void CAdasManager::quit()
{
   TRC_SCOPE(ADAS, CAdasManager, quit);
   DBG_MSG(("CAdasManager::quit()\n"));
   m_bQuit = true;
   m_event.set();

}

void CAdasManager::join()
{
   m_hThread.join();
}

void CAdasManager::resume()
{
	m_event.set();
}

void CAdasManager::pushMessage(const tagBaseMessage& rMsg, UInt32 uiLen)
{
	if(m_pMsgQueue )
	{
		//DBG_MSG(("CAdasManager::pushMessage\n"));
		m_pMsgQueue->pushMessage(rMsg, uiLen);

		m_event.set();
	}
}
