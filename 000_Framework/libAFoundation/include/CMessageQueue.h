
#ifndef __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CMESSAGE_QUEUE_H
#define __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CMESSAGE_QUEUE_H

#include "platformdef.h"
#include "TraceMacros.h"
#include "CMessageHandler.h"
#include "TypeDefine.h"
#include "MessageForQueue.h"

using namespace std;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

class CMessageQueue
{
public:
    enum EType
    {
        ET_BLOCK        = 0X00000001,
        ET_NONBLOCK     = 0X00000002,
    };

public:
    CMessageQueue(const string& strMsgQueueName, UInt32 uiQueueMaxSize, CMessageHandler* pHandler);
    virtual ~CMessageQueue();

    VOID            pushMessage(MessageForQueue* rMsg, Int32 uiMsgLen=0);
    virtual VOID    handleMessageQueue();

    BOOLEAN            isEmpty();
    //virtual VOID  blockHandleMessageQueue();

protected:
    VOID    _handleMessageQueue();

private:
    string                    m_strMsgQueueName;
    queue<MessageForQueue*>     m_iMsgQueue;

    mutex mEventlockMutex;
    condition_variable  mWaitEventCondVar;

    MessageForQueue* m_pEventData;

    CMessageHandler* m_pHandler;
};

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CMESSAGE_QUEUE_H