
#ifdef LINUX_OS
#include "../include/CMQRunnableService.h"
#else
#include "..\include\CMQRunnableService.h"
#endif

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

CMQRunnableService::CMQRunnableService(const string& strName, CMessageQueue* pMsgQueue)
    : CRunableBase(strName, TRUE)
    , m_bInitialized(FALSE)
    , m_strRName(strName)
    , m_pMsgQueue(pMsgQueue)
{
}

CMQRunnableService::~CMQRunnableService()
{
    if(m_pMsgQueue)
    {
        delete  m_pMsgQueue;
        m_pMsgQueue = nullptr;
    }
}

VOID CMQRunnableService::start()
{
    if(m_pMsgQueue == NULL)
    {
        ALOGE("start m_pMsgQueue is NULL\n");
        return;
    }

    CRunableBase::start();
}

VOID CMQRunnableService::pushMessage(MessageForQueue* rMsg, Int32 ilen)
{
    std::unique_lock<mutex>lock_msg(mEventlockMutex);
    if(m_pMsgQueue)
    {
        m_pMsgQueue->pushMessage(rMsg, ilen);
        resume();
    }
    else
    {
        ALOGE("CMQRunnableService::pushMessage m_pMsgQueue is null, SerialNumber = %u do not push into messageQueue\n",
                rMsg->m_uiSerialNumber);
    }
}

VOID CMQRunnableService::update()
{

    m_pMsgQueue->handleMessageQueue();
}

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman