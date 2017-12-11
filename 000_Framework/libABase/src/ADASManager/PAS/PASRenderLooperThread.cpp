
#include "ADASManager/PAS/PASRenderLooperThread.h"
#include "ADASManager/PAS/GraphicCore/PasUtils.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

PASMessageHandler::PASRenderLooperThread::PASRenderLooperThread(const string& name, CMessageQueue* msg)
    : CMQRunnableService(name, msg)
{
    m_pGraphic = new CAdasGraphic();

    InitSurfaceInfo();
    InitBackGround();
    InitCar();
    InitCompoundedArea();

    start();
}

PASMessageHandler::PASRenderLooperThread::~PASRenderLooperThread()
{
    PasManager::DelInstance();

    if(m_pGraphic != nullptr) {
        delete m_pGraphic;
        m_pGraphic = nullptr;
    }

    quit();
}

VOID PASMessageHandler::PASRenderLooperThread::InitSurfaceInfo()
{
    m_structRenderData.surfaceID = PAS_SURFACE_ID;

    tsurfaceInfo surfaceInfo;
    surfaceInfo.surfaceName = PAS_SURFACE_NAME;
    surfaceInfo.surfaceId = PAS_SURFACE_ID;
    surfaceInfo.moduleType = MODULE_PAS;
    surfaceInfo.bActiveEGL = TRUE;
    surfaceInfo.viewPos.width = PAS_SCREEN_WIDTH;
    surfaceInfo.viewPos.height = PAS_SCREEN_HIGHT;
    surfaceInfo.viewPos.viewPos.x = 0;
    surfaceInfo.viewPos.viewPos.y = 0;

    m_structSurfaceArray.push_back(surfaceInfo);
}

VOID PASMessageHandler::PASRenderLooperThread::InitBackGround()
{
    tbufInfo BackGroundbufferInfo;
    BackGroundbufferInfo.buffer = PasManager::GetInstance()->m_pHasCompoundedBackGround;
    BackGroundbufferInfo.width = PAS_SCREEN_WIDTH;
    BackGroundbufferInfo.height = PAS_SCREEN_HIGHT;
    BackGroundbufferInfo.bRender = TRUE;
    m_structRenderData.bufferMap.insert(make_pair(ADAS_PAS_BACKGROUND_STATUS, BackGroundbufferInfo));
}

VOID PASMessageHandler::PASRenderLooperThread::InitCar()
{
    tbufInfo carInfo;
    carInfo.buffer = PasManager::GetInstance()->m_pCarBuffer;
    carInfo.width = PAS_SCREEN_WIDTH;
    carInfo.height = PAS_SCREEN_HIGHT;
    carInfo.bRender = TRUE;
    m_structRenderData.bufferMap.insert(make_pair(ADAS_PAS_CAR_STATUS, carInfo));
}

VOID PASMessageHandler::PASRenderLooperThread::InitCompoundedArea()
{
    tbufInfo compoundedAreaInfo;
    compoundedAreaInfo.buffer = PasManager::GetInstance()->m_pHasCompoundedArea;
    compoundedAreaInfo.width = PAS_SCREEN_WIDTH;
    compoundedAreaInfo.height = PAS_SCREEN_HIGHT;
    compoundedAreaInfo.bRender = TRUE;
    m_structRenderData.bufferMap.insert(make_pair(ADAS_PAS_RADAR_STATUS, compoundedAreaInfo));
}

UInt32 PASMessageHandler::s_mMessageInQueueCount = 0;

VOID PASMessageHandler::SendMessage(MessageForQueue* msg)// const
{
    m_lock.lock();
    if(s_mMessageInQueueCount < 20) {
        m_pPASRenderLooperThread->pushMessage(msg);
        s_mMessageInQueueCount++;
    } else {
        ALOGE("PASMessageHandler s_mMessageInQueueCount > 20 !!!!!!\n");
    }
    m_lock.unlock();
}

//-----------------------------render thread called---------------------------------------------------------
BOOLEAN PASMessageHandler::PASRenderLooperThread::initialize(string sServiceName)
{
    m_pGraphic->createSurface(m_structSurfaceArray);
    m_pGraphic->Render(m_structRenderData); // default screen
    return TRUE;
}

VOID PASMessageHandler::_handle(UInt32 uiType, UInt32 uiEventID, const string& pData)
{
    m_lock.lock();
    s_mMessageInQueueCount--;
    m_lock.unlock();
    m_pPASRenderLooperThread->m_pGraphic->Render(m_pPASRenderLooperThread->m_structRenderData);  //Compound screen
}
//-----------------------------render thread called---------------------------------------------------------

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman