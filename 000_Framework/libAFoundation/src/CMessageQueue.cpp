
#ifdef LINUX_OS
#include "../include/CMessageQueue.h"
#else
#include "..\include\CMessageQueue.h"
#endif

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

#define PWM_MSG_BUF_LEN 32

CMessageQueue::CMessageQueue(const string& strMsgQueueName, UInt32 uiQueueMaxSize, CMessageHandler* pHandler)
    : m_strMsgQueueName(strMsgQueueName, TRUE)
    //, m_iMsgQueue(-1)
    , m_pHandler(pHandler)
{
    ALOGD("create message queue : %s\n", strMsgQueueName.c_str());

#if 0
    if( strMsgQueueName.length() > 0 && uiQueueMaxSize > 0 )
    {
        struct mq_attr attr;
        memset((VOID*)&attr, 0, sizeof(struct mq_attr));
        attr.mq_msgsize = PWM_MSG_BUF_LEN;
        attr.mq_maxmsg = uiQueueMaxSize;


        mq_unlink(strMsgQueueName.c_str());
        m_iMsgQueue = mq_open(strMsgQueueName.c_str(), O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, &attr);
        if (-1 == m_iMsgQueue)
        {
          PAM_LOG_INFO(("open mqueue erro, error number is \n"));
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
    mThreadExit = TRUE;
    RVCEvents l_EventData;
    l_EventData.EventID =  RVC_EXIT_REQUEST;
    postEvent(l_EventData);
    //Wait till message queue Thread returns
    mEventThread.join();
    //Wait till Nano message Thread returns
    mNanoMsgThread.join();
    #endif
}

VOID CMessageQueue::pushMessage(MessageForQueue* rMsg, Int32 uiMsgLen)
{
    //PDCC_LOG_INFO("start -- CMessageQueue::pushMessage: rMsg._uiType[%d] - rMsg._pData[%d] -len[%d] \n",rMsg._uiType,(Int32)*rMsg._pData,uiMsgLen) ;
    //post the event to message queue thread and signal to come out from blocking wait
#ifdef QNX_OS
    if (pthread_mutex_lock(&mEventlockMutex))
        return;
    m_iMsgQueue.push(rMsg);
    pthread_mutex_unlock(&mEventlockMutex);
#endif
#ifdef LINUX_OS
    unique_lock<mutex>lock_msg(mEventlockMutex, defer_lock);
    //todo a commom internal msg used for ADAS pres
    lock_msg.lock();
    m_iMsgQueue.push(rMsg);
    lock_msg.unlock();
#endif
#ifdef WIN_OS
    mEventlockMutex.lock();
    m_iMsgQueue.push(rMsg);
    mEventlockMutex.unlock();
#endif
   // mWaitEventCondVar.notify_one();
    //PDCC_LOG_INFO("end -- CMessageQueue::pushMessage: rMsg._uiType\n") ;

}
//TRC_SCOPE_DEF(ADAS, CMessageQueue, handleMessageQueue);
VOID CMessageQueue::handleMessageQueue()
{
    //UInt32 msg[PWM_MSG_BUF_LEN] = {0};
    ALOGD("handleMessageQueue() start\n") ;
#ifdef QNX_OS
    ;
#endif
#ifdef LINUX_OS
    unique_lock<mutex>lock(mEventlockMutex, defer_lock);
#endif
#ifdef WIN_OS
    mEventlockMutex.lock();
#endif
    //while(TRUE)
   // {
        //if(!mThreadExit)
       // {
       //    PAM_LOG_INFO("processEventQueue is waiting for events") ;
       //     mWaitEventCondVar.wait(lock);
      //  }
       // lock.unlock();

        while(TRUE)
        {
            #ifdef QNX_OS
                pthread_mutex_lock(&mEventlockMutex);
            #endif
            #ifdef LINUX_OS
                lock.lock();
            #endif
            #ifdef WIN_OS
                mEventlockMutex.lock();
            #endif
            if(m_iMsgQueue.empty())
            {
                ALOGD("handleMessageQueue() m_iMsgQueue.empty()\n") ;
                break;
            } else {
                m_pEventData = m_iMsgQueue.front();
             //   mEventQueue.pop();
                if( m_pHandler )
                {
                    ALOGD("handleMessageQueue() handle\n") ;
                    m_pHandler->handle(m_pEventData);
                }
               // switch(m_pEventData.EventID)
              //  {

                //}
                m_iMsgQueue.pop();
                delete m_pEventData;
            }
            #ifdef QNX_OS
                pthread_mutex_unlock(&mEventlockMutex);
            #endif
            #ifdef LINUX_OS
                lock.unlock();
            #endif
            #ifdef WIN_OS
                mEventlockMutex.unlock();
            #endif

        }

    //    if(mThreadExit)
     //   {
     //       break;

    //    }

    //}
    #ifdef QNX_OS
        pthread_mutex_unlock(&mEventlockMutex);
    #endif
    #ifdef LINUX_OS
        lock.unlock();
    #endif
    #ifdef WIN_OS
        mEventlockMutex.unlock();
    #endif
    ALOGD("handleMessageQueue() end\n") ;
}

BOOLEAN CMessageQueue::isEmpty()
{
    //struct mq_attr attr;
    //memset(&attr, 0, sizeof(attr));
    //mq_getattr(m_iMsgQueue,&attr);
    //check whether the message queue is empty, if not receive the message and write to UISS
    //if( attr.mq_curmsgs > 0 )
    //    return FALSE;

    return TRUE;
}

VOID CMessageQueue::_handleMessageQueue()
{

}

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman