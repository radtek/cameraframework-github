
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
    , m_pHandler(pHandler)
{
    ALOGD("create message queue : %s\n", strMsgQueueName.c_str());
}

CMessageQueue::~CMessageQueue()
{

}

VOID CMessageQueue::pushMessage(MessageForQueue* rMsg, Int32 uiMsgLen)
{
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
    ALOGD("CMessageQueue::pushMessage : SerialNumber = %u, MeaasgeID = %u ^^^^^^^^^^^^^^\n",rMsg->m_uiSerialNumber, rMsg->m_uiMeaasgeID);
    lock_msg.unlock();
#endif
#ifdef WIN_OS
    mEventlockMutex.lock();
    m_iMsgQueue.push(rMsg);
    mEventlockMutex.unlock();
#endif
}

VOID CMessageQueue::handleMessageQueue()
{
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
                ALOGD("CMessageQueue::handleMessageQueue : SerialNumber = %u, MeaasgeID = %u vvvvvvvvvvvvvvv\n",
                        m_pEventData->m_uiSerialNumber, m_pEventData->m_uiMeaasgeID);

                if( m_pHandler )
                {
                    ALOGD("handleMessageQueue() handle\n") ;
                    m_pHandler->handle(m_pEventData);
                }

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
    return TRUE;
}

VOID CMessageQueue::_handleMessageQueue()
{
}

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman