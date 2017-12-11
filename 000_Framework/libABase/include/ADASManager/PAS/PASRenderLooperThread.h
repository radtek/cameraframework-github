
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_PASRENDERLOOPERTHREAD_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_PASRENDERLOOPERTHREAD_H__

#include "CMQRunnableService.h"
#include "CMessageQueue.h"
#include "CMessageHandler.h"
#include "MessageForQueue.h"
#include "AGraphic.h"
#include "ADASManager/PAS/PasManager.h"

#include <mutex>

using namespace std;

using Harman::Adas::AFramework::AFoundation::CMessageQueue;
using Harman::Adas::AFramework::AFoundation::CMessageHandler;
using Harman::Adas::AFramework::AFoundation::MessageForQueue;
using Harman::Adas::AFramework::AFoundation::CMQRunnableService;
using Harman::Adas::AFramework::AGraphic::CAdasGraphic;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class PASMessageHandler : public CMessageHandler
{
private:
    class PASRenderLooperThread : public CMQRunnableService
    {
    public:
        PASRenderLooperThread(const string& name, CMessageQueue* msg);

        ~PASRenderLooperThread();

        virtual BOOLEAN initialize(string sServiceName) override;

    private:
        VOID InitSurfaceInfo();

        VOID InitBackGround();

        VOID InitCar();

        VOID InitCompoundedArea();

    public:
        CAdasGraphic* m_pGraphic = nullptr;

        trenderData m_structRenderData;

        tsurfaceList m_structSurfaceArray;
    };

public:
    PASMessageHandler()
    {
        m_pMessageQueue = new CMessageQueue("PASMessageQueue", 300, this);
        m_pPASRenderLooperThread = new PASRenderLooperThread("PASRenderLooperThread", m_pMessageQueue);
        PasManager::GetInstance()->SetHandler(this);
    }

    VOID SendMessage(MessageForQueue* msg);// const;

    ~PASMessageHandler()
    {
        if(m_pMessageQueue != nullptr) {
            delete m_pMessageQueue;
            m_pMessageQueue = nullptr;
        }

        if(m_pPASRenderLooperThread != nullptr) {
            delete m_pPASRenderLooperThread;
            m_pPASRenderLooperThread = nullptr;
        }
    }

protected:
    virtual VOID _handle(UInt32 uiType, UInt32 uiEventID, const string& pData) override;

public:
    CMessageQueue* m_pMessageQueue = nullptr;
    PASRenderLooperThread* m_pPASRenderLooperThread = nullptr;

private:
    std::mutex m_lock;
    static UInt32 s_mMessageInQueueCount;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_PASRENDERLOOPERTHREAD_H__