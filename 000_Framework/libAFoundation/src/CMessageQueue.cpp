
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

    unique_lock<mutex>lock_msg(mEventlockMutex, defer_lock);
    //todo a commom internal msg used for ADAS pres
    lock_msg.lock();
    m_iMsgQueue.push(rMsg);
    ALOGD("CMessageQueue::pushMessage : SerialNumber = %u, MeaasgeID = %u ^^^^^^^^^^^^^^\n",rMsg->m_uiSerialNumber, rMsg->m_uiMeaasgeID);
    lock_msg.unlock();
}

VOID CMessageQueue::handleMessageQueue()
{
    ALOGD("handleMessageQueue() start\n") ;
    unique_lock<mutex>lock(mEventlockMutex, defer_lock);

    while(TRUE)
    {
        
        lock.lock();

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
        
        lock.unlock();
    }

    lock.unlock();
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