#include "CMessageQueue.h"


#define PWM_MSG_BUF_LEN 32
TRC_SCOPE_DEF(ADAS, CMessageQueue, CMessageQueue);
CMessageQueue::CMessageQueue(const string& strMsgQueueName, unsigned int uiQueueMaxSize, CMessageHandler* pHandler)
: m_strMsgQueueName(strMsgQueueName)
, m_iMsgQueue(-1)
, m_pHandler(pHandler)
{
	TRC_SCOPE(ADAS, CMessageQueue, CMessageQueue);
	if( strMsgQueueName.length() > 0 && uiQueueMaxSize > 0 )
	{
		struct mq_attr attr;
		memset((void*)&attr, 0, sizeof(struct mq_attr));
		attr.mq_msgsize = PWM_MSG_BUF_LEN;
		attr.mq_maxmsg = uiQueueMaxSize;


		mq_unlink(strMsgQueueName.c_str());
		m_iMsgQueue = mq_open(strMsgQueueName.c_str(), O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, &attr);
		if (-1 == m_iMsgQueue)
		{
		  DBG_MSG(("open mqueue erro, error number is \n"));
		}
	}
}

CMessageQueue::~CMessageQueue()
{
	if( m_iMsgQueue != -1 )
	{
		mq_close(m_iMsgQueue);
		mq_unlink(m_strMsgQueueName.c_str());
	}
}

void CMessageQueue::pushMessage(const tagBaseMessage& rMsg, UInt32 uiMsgLen)
{
	//DBG_MSG(("push msg = %u\n", UInt32(pMsg)));
	mq_send(m_iMsgQueue, (char*)(&rMsg), uiMsgLen,  0);
}
//TRC_SCOPE_DEF(ADAS, CMessageQueue, handleMessageQueue);
void CMessageQueue::handleMessageQueue()
{
	UInt32 msg[PWM_MSG_BUF_LEN] = {0};
	while(TRUE)
    {
	  memset(msg, 0, PWM_MSG_BUF_LEN);
	  struct mq_attr attr;
	  memset(&attr, 0, sizeof(attr));
	  mq_getattr(m_iMsgQueue,&attr);
	  //check whether the message queue is empty, if not receive the message and write to UISS
	  if( attr.mq_curmsgs > 0 )
	  {
         //TRC_SCOPE(ADAS, CMessageQueue, handleMessageQueue);
		 mq_receive( m_iMsgQueue, (char*)msg, attr.mq_msgsize, NULL );
		 //DBG_MSG(("XXXXXXXXX que- %s receive msg = %u @ msg num =%d XXXXXXX\n",m_strMsgQueueName.c_str(), msg[0],attr.mq_curmsgs));

		if( m_pHandler )
		{
			m_pHandler->handle(msg);
		}


	  }
	  else
	  {
		  usleep(10000);
		  break;
	  }
    }

}

BOOLEAN	CMessageQueue::isEmpty()
{
	struct mq_attr attr;
	memset(&attr, 0, sizeof(attr));
	mq_getattr(m_iMsgQueue,&attr);
	//check whether the message queue is empty, if not receive the message and write to UISS
	if( attr.mq_curmsgs > 0 )
		return FALSE;

	return TRUE;

}

void CMessageQueue::_handleMessageQueue()
{

}

