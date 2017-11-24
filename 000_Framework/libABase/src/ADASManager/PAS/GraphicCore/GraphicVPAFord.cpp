
#include "ADASManager/PAS/GraphicCore/GraphicVPAFord.h"
#include "ADASManager/PAS/GraphicCore/PasUtils.h"
#include "ADASManager/PAS/ResourcePngDefine.h"
#include "ADASManager/PAS/Area.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

GraphicVPAFord::GraphicVPAFord()
    : CRunableBase("GraphicVPAFord", false)
{
    ALOGD(" [%s, %d] GraphicVPAFord::GraphicVPAFord() \n", __FUNCTION__, __LINE__);

    renderData1.surfaceID = 52;

    tsurfaceInfo surfaceInfo;
    surfaceInfo.surfaceName = "PAS_SURFACE";
    surfaceInfo.surfaceId = 52;
    surfaceInfo.moduleType = MODULE_PAS;
    surfaceInfo.bActiveEGL = TRUE;
    surfaceInfo.viewPos.width = 640;//width;
    surfaceInfo.viewPos.height = 720;//height;
    surfaceInfo.viewPos.viewPos.x = 0;
    surfaceInfo.viewPos.viewPos.y = 0;

    surfaceArry.push_back(surfaceInfo);

    unsigned int width, height;
    buffer1 = PasUtils::LodePNGImage(PDC_CAR, &width, &height, FALSE, nullptr);
    tbufInfo bufferInfo1;
    bufferInfo1.buffer = buffer1;
    bufferInfo1.width = width;
    bufferInfo1.height = height;
    bufferInfo1.bRender = TRUE;
    renderData1.bufferMap.insert(make_pair(ADAS_PAS_CAR_STATUS, bufferInfo1));


    tbufInfo DefaultAreabufferInfo;
    DefaultAreabufferInfo.buffer = PasManager::GetInstance()->m_pDefaultArea->m_pHasCompoundedArea;
    DefaultAreabufferInfo.width = 152;
    DefaultAreabufferInfo.height = 228;
    DefaultAreabufferInfo.bRender = TRUE;
    renderData1.bufferMap.insert(make_pair(ADAS_PAS_RADAR_STATUS, DefaultAreabufferInfo));


    //buffer3 = PasUtils::LodePNGImage(PDC_BACKGROUND, &width, &height, FALSE, nullptr);
    buffer3 = (unsigned char*)malloc(640*720*4);
    if(NULL != buffer3)
    {
        memset(buffer3, 87, 640*720*4);
    }
    for(int i = 0; i < 640*720*4;){
        buffer3[i+3] = 255;
        i += 4;
    }

    // buffer3 = (unsigned char*)malloc(640*720*4);
    // if(NULL != buffer3)
    // {
    //     memset(buffer3, 255, 640*720*4);
    // }

    tbufInfo BackGroundbufferInfo;
    BackGroundbufferInfo.buffer = buffer3;
    BackGroundbufferInfo.width = 640;
    BackGroundbufferInfo.height = 720;
    BackGroundbufferInfo.bRender = TRUE;
    renderData1.bufferMap.insert(make_pair(ADAS_PAS_WARNING_STATUS, BackGroundbufferInfo));


    graphic = new CAdasGraphic();
}

GraphicVPAFord::~GraphicVPAFord()
{
    free(buffer1);
    free(buffer3);

    PasManager::DelInstance();
}

bool GraphicVPAFord::vInit(int screenWidth, int screenHeight)
{
    ALOGD(" [%s, %d]\n", __FUNCTION__, __LINE__);

    setscSize(screenWidth,screenHeight);
	return false;
}

VOID GraphicVPAFord::init()
{
    ALOGD("GraphicVPAFord::init() :: createSurface \n");
    graphic->createSurface(surfaceArry);
}

void GraphicVPAFord::update()
{
    ALOGD("GraphicVPAFord::update() :: Render\n");

    //auto it1 = renderData1.bufferMap.find(ADAS_PAS_RADAR_STATUS);

    //-------------------------------------FrontLeftInside

    PasManager::GetInstance()->m_pFrontLeftInside->m_vFrontLeftInsideColorBlockArray[2]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontLeftInside->m_vFrontLeftInsideColorBlockArray[1]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontLeftInside->m_vFrontLeftInsideColorBlockArray[0]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    //-------------------------------------------FrontLeft

    PasManager::GetInstance()->m_pFrontLeft->m_vFrontLeftColorBlockArray[3]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontLeft->m_vFrontLeftColorBlockArray[2]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontLeft->m_vFrontLeftColorBlockArray[1]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontLeft->m_vFrontLeftColorBlockArray[0]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    //-------------------------------------------------FrontRight

    PasManager::GetInstance()->m_pFrontRight->m_vFrontRightColorBlockArray[3]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontRight->m_vFrontRightColorBlockArray[2]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontRight->m_vFrontRightColorBlockArray[1]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontRight->m_vFrontRightColorBlockArray[0]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    //--------------------------------------------FrontRightInside

    PasManager::GetInstance()->m_pFrontRightInside->m_vFrontRightInsideColorBlockArray[2]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontRightInside->m_vFrontRightInsideColorBlockArray[1]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontRightInside->m_vFrontRightInsideColorBlockArray[0]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    //----------------------------------------------RearLeftInside

    PasManager::GetInstance()->m_pRearLeftInside->m_vRearLeftInsideColorBlockArray[3]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeftInside->m_vRearLeftInsideColorBlockArray[2]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeftInside->m_vRearLeftInsideColorBlockArray[1]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeftInside->m_vRearLeftInsideColorBlockArray[0]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);


    //-------------------------------------------RearLeft

    PasManager::GetInstance()->m_pRearLeft->m_vRearLeftColorBlockArray[6]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeft->m_vRearLeftColorBlockArray[5]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeft->m_vRearLeftColorBlockArray[4]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeft->m_vRearLeftColorBlockArray[3]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeft->m_vRearLeftColorBlockArray[2]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeft->m_vRearLeftColorBlockArray[1]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeft->m_vRearLeftColorBlockArray[0]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    //-------------------------------------------------RearRight

    PasManager::GetInstance()->m_pRearRight->m_vRearRightColorBlockArray[6]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRight->m_vRearRightColorBlockArray[5]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRight->m_vRearRightColorBlockArray[4]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRight->m_vRearRightColorBlockArray[3]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRight->m_vRearRightColorBlockArray[2]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRight->m_vRearRightColorBlockArray[1]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRight->m_vRearRightColorBlockArray[0]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);



    //----------------------------------------------RearRightInside

    PasManager::GetInstance()->m_pRearRightInside->m_vRearRightInsideColorBlockArray[3]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRightInside->m_vRearRightInsideColorBlockArray[2]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRightInside->m_vRearRightInsideColorBlockArray[1]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRightInside->m_vRearRightInsideColorBlockArray[0]->CompoundArea();
    graphic->Render(renderData1);
    sleep(1);
}

void GraphicVPAFord::setscSize(int screenWidth,int screenHeight)
{
    m_iHeight = screenHeight;
    m_iWidth = screenWidth;
}

int GraphicVPAFord::getScSizeWidth()
{
    return m_iWidth;
}

int GraphicVPAFord::getScSizeHeight()
{
    return m_iHeight;
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman