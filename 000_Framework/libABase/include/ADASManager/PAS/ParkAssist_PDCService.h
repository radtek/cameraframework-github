
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_PDCSERVICE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_PDCSERVICE_H__

#include <string>

#include "CMQRunnableService.h"
#include "CMessageQueue.h"
#include "PDCContext.h"
#include "PDCGraphic.h"
#include "TraceMacros.h"

using namespace std;

using Harman::Adas::AFramework::AFoundation::CMQRunnableService;
using Harman::Adas::AFramework::AFoundation::CMessageQueue;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class CPDCService : public CMQRunnableService
{
public:
    enum ePDCState {
        eSTOP,
        eRUN,
        ePAUSE,
        eFAULT,
        eMISSING
    };
    virtual ~CPDCService(){};
    CPDCService(const std::string& strName="PDCService", CMessageQueue* pMsgQueue=NULL);
    virtual int iPDCInit();
    virtual int iPDCStart();
    virtual int iPDCPause();
    virtual int PDCResume();
    virtual int PDCStop();
    virtual int PDCExit() ;
    virtual void beforeHandleMsgQueue();
    virtual void afterHandleMsgQueue();

    bool initialize();
    bool unitialize();

protected:
    ePDCState m_ePDCState;
    PDCGraphic* m_PDCGraphic;

private:
    PDCContext m_PDCContext;
    virtual void vSyncLayers() = 0;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_PDCSERVICE_H__