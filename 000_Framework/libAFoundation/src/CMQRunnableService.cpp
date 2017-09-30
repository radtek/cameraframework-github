
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
    , m_pMsgQueue(pMsgQueue)
{
    if(!m_pMsgQueue) {
        ALOGD("m_pMsgQueue is NULL \n");
    }
}

CMQRunnableService::~CMQRunnableService()
{
    if(m_pMsgQueue)
    {
        delete  m_pMsgQueue;
        m_pMsgQueue = nullptr;
        //ref object feature
        //m_pMsgQueue->release();
    }
}

VOID CMQRunnableService::start()
{
    if(m_pMsgQueue == NULL)
    {
        ALOGD("start pMsgQueue is NULL\n");
        return;
    }

    CRunableBase::start();
}

VOID CMQRunnableService::pushMessage(MessageForQueue* rMsg, Int32 ilen)
{
    if(m_pMsgQueue)
    {
        //PDCC_LOG_INFO("CMQRunnableService::pushMessage: rMsg._uiType[%d] - rMsg._pData[%d][%d] -len[%d] \n",rMsg->_uiType,(Int32)rMsg._pData[0],(Int32)rMsg._pData[1],ilen) ;
        //insert message into messageQueue
        m_pMsgQueue->pushMessage(rMsg, ilen);
        //wake up, get message from messageQueue,and handle message
        ALOGD("CMQRunnableService::pushMessage call resume ***********************\n");
        resume();
    }else{
        ALOGE("CMQRunnableService::pushMessage m_pMsgQueue is null, SerialNumber = %u do not push into messageQueue\n",
                rMsg->m_uiSerialNumber);
    }
}

VOID CMQRunnableService::update()
{
    beforeHandleMessageQueue();

    m_pMsgQueue->handleMessageQueue();

    afterHandleMessageQueue();
}

VOID CMQRunnableService::beforeHandleMessageQueue()
{
    ALOGD("beforeHandleMessageQueue\n");
}

VOID CMQRunnableService::afterHandleMessageQueue()
{
    //msg que is empty, wait next push to resume
    ALOGD("afterHandleMessageQueue \n");
    pause();
    ALOGD("afterHandleMessageQueue resume\n");
}

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman