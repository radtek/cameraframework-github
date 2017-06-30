#include "CMessageQueue.h"


#define PWM_MSG_BUF_LEN 32
CMessageQueue::CMessageQueue(const string& strMsgQueueName, unsigned int uiQueueMaxSize, CMessageHandler* pHandler)
: m_strMsgQueueName(strMsgQueueName,true)
//, m_iMsgQueue(-1)
, m_pHandler(pHandler)
{
	PAM_LOG_INFO(strMsgQueueName.c_str());

#if 0
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
#endif
}

CMessageQueue::~CMessageQueue()
{
	//if( m_iMsgQueue !=  NULL)
	{
		//mq_close(m_iMsgQueue);
		//mq_unlink(m_strMsgQueueName.c_str());
	}
	#if 0
	//Sending dummy message to unblock the message queue incase if it's empty
	mThreadExit = true;
	RVCEvents l_EventData;
	l_EventData.EventID =  RVC_EXIT_REQUEST;
	postEvent(l_EventData);
	//Wait till message queue Thread returns
    mEventThread.join(); 
	//Wait till Nano message Thread returns
    mNanoMsgThread.join(); 
	#endif
}

void CMessageQueue::pushMessage(const tagBaseMessage& rMsg, int uiMsgLen)
{
	//PDCC_LOG_INFO("start -- CMessageQueue::pushMessage: rMsg._uiType[%d] - rMsg._pData[%d] -len[%d] \n",rMsg._uiType,(int)*rMsg._pData,uiMsgLen) ;
	//post the event to message queue thread and signal to come out from blocking wait
    unique_lock<mutex>lock_msg(mEventlockMutex,std::defer_lock);
	//todo a commom internal msg used for ADAS pres
	lock_msg.lock();
    m_iMsgQueue.push(rMsg);
    lock_msg.unlock();
   // mWaitEventCondVar.notify_one();
    //PDCC_LOG_INFO("end -- CMessageQueue::pushMessage: rMsg._uiType\n") ;

}
//TRC_SCOPE_DEF(ADAS, CMessageQueue, handleMessageQueue);
void CMessageQueue::handleMessageQueue()
{
	//unsigned int msg[PWM_MSG_BUF_LEN] = {0};
	PDCC_LOG_INFO("CMessageQueue::handleMessageQueue() start") ;
	unique_lock<mutex>lock(mEventlockMutex,std::defer_lock);
    //while(true)
   // {
		//if(!mThreadExit)
       // {
       //    PAM_LOG_INFO("processEventQueue is waiting for events") ;
       //     mWaitEventCondVar.wait(lock);
      //  }
       // lock.unlock();

        while(true)
        {
            lock.lock();
            if(m_iMsgQueue.empty())
            {
            	PDCC_LOG_INFO("CMessageQueue::handleMessageQueue() m_iMsgQueue.empty()") ;
				break;
            }
            else 
            {
        
                mEventData = m_iMsgQueue.front();
             //   mEventQueue.pop();
				if( m_pHandler )
				{
					PDCC_LOG_INFO("CMessageQueue::handleMessageQueue() handle") ;
					m_pHandler->handle(&mEventData);
				}
               // switch(mEventData.EventID)
              //  {
                
				//}
				m_iMsgQueue.pop();
			}	
			lock.unlock();
		}
		
	//	if(mThreadExit)
     //   {
     //       break;

    //    }

	//}
	lock.unlock();
	PDCC_LOG_INFO("CMessageQueue::handleMessageQueue() end") ;
}

bool CMessageQueue::isEmpty()
{
	//struct mq_attr attr;
	//memset(&attr, 0, sizeof(attr));
	//mq_getattr(m_iMsgQueue,&attr);
	//check whether the message queue is empty, if not receive the message and write to UISS
	//if( attr.mq_curmsgs > 0 )
	//	return false;

	return true;

}

void CMessageQueue::_handleMessageQueue()
{

}

