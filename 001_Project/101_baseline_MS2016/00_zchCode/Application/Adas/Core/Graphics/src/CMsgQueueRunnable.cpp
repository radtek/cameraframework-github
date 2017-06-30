
#include "CMsgQueueRunnable.h"

CMsgQueueRunnable::CMsgQueueRunnable(const string& strName,CEvent::CALLBACK func)
: CRunnable(strName, func)
, m_bInitialized(FALSE)
, m_pMsgQueue(NULL)
{

}

CMsgQueueRunnable::~CMsgQueueRunnable()
{
	if( m_pMsgQueue )
	{
		m_pMsgQueue->release();
	}
}
TRC_SCOPE_DEF(ADAS, CMsgQueueRunnable, start);
void CMsgQueueRunnable::start(void* pMsgQueue)
{
	TRC_SCOPE(ADAS, CMsgQueueRunnable, start);
	if( pMsgQueue == NULL )
	{
		DBG_MSG(("CRunnable::start pMsgQueue is NULL\n"));
		return;
	}

	m_pMsgQueue = (CMessageQueue*)pMsgQueue;

	CRunnable::start();
}

void CMsgQueueRunnable::pushMessage(const tagBaseMessage& rMsg, UInt32 uiLen)
{
	if( m_pMsgQueue )
	{
		m_pMsgQueue->pushMessage(rMsg, uiLen);
	}
}

void CMsgQueueRunnable::update()
{
	beforeHandleMessageQueue();

//		DBG_MSG(("handleMessageQueue begin.\n"));
	m_pMsgQueue->handleMessageQueue();
//		DBG_MSG(("handleMessageQueue end.\n"));

	afterHandleMessageQueue();
}

void CMsgQueueRunnable::beforeHandleMessageQueue()
{
	;
}

void CMsgQueueRunnable::afterHandleMessageQueue()
{
	;
}

