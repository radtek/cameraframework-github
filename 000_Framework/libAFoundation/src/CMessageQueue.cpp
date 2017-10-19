
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
    : m_strMsgQueueName(strMsgQueueName)
    , m_pHandler(pHandler)
{
    ALOGD("create message queue : [%s]\n", strMsgQueueName.c_str());
}

CMessageQueue::~CMessageQueue()
{

}

VOID CMessageQueue::pushMessage(MessageForQueue* rMsg, Int32 uiMsgLen)
{
    if(m_iMsgQueue.size() < MSQ_MAXSIZE + 1) {
        m_iMsgQueue.push(rMsg);
        ALOGD("[%s]: SerialNumber = %u, MeaasgeID = %u ^^^^^^^^^^^^^^\n",
        m_strMsgQueueName.c_str(),
        rMsg->m_uiSerialNumber, rMsg->m_uiMeaasgeID);
    }
    else{
        ALOGD("[%s]: boom size = [%d]!!!!\n", m_iMsgQueue.size());  
    }
}

VOID CMessageQueue::handleMessageQueue()
{
    while(TRUE)
    {
        if(m_iMsgQueue.empty())
        {
            ALOGE("msq [%s] is empty()\n", m_strMsgQueueName.c_str()) ;
            break;
        } else {
            m_pEventData = m_iMsgQueue.front();
            ALOGD("[%s]: SerialNumber = %u, MeaasgeID = %u vvvvvvvvvvvvvvv\n",
                    m_strMsgQueueName.c_str(),
                    m_pEventData->m_uiSerialNumber, m_pEventData->m_uiMeaasgeID);

            if(m_pHandler)
            {
                m_pHandler->handle(m_pEventData);
            }

            m_iMsgQueue.pop();
            delete m_pEventData;
        }
    }
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