
#ifndef __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION__CMQRUNNABLESERVICE_H__
#define __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION__CMQRUNNABLESERVICE_H__

#include "platformdef.h"
#include "TraceMacros.h"
#include "CRunableBase.h"
#include "CMessageQueue.h"
#include "MessageForQueue.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

class CMQRunnableService : public CRunableBase {
public:
    CMQRunnableService(const string& strName = "NameNotSet", CMessageQueue* pMsgQueue = NULL);
    virtual ~CMQRunnableService();
    virtual VOID pushMessage(MessageForQueue* rMsg, Int32 ilen = 0);
    virtual VOID start();
    BOOLEAN initialize(string sServiceName);
    BOOLEAN unitialize();

protected:
    virtual VOID update();
    virtual VOID beforeHandleMessageQueue();
    virtual VOID afterHandleMessageQueue();
    VOID setMsgQueue(CMessageQueue* pMsgQueue){m_pMsgQueue = pMsgQueue;};

private:
    BOOLEAN m_bInitialized;
    CMessageQueue* m_pMsgQueue;
};

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION__CMQRUNNABLESERVICE_H__