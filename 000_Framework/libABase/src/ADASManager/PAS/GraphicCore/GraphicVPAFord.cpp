
#include "ADASManager/PAS/GraphicCore/GraphicVPAFord.h"
#include "ADASManager/PAS/GraphicCore/PasUtils.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

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
    surfaceInfo.viewPos.width = 640;
    surfaceInfo.viewPos.height = 720;
    surfaceInfo.viewPos.viewPos.x = 0;
    surfaceInfo.viewPos.viewPos.y = 0;

    surfaceArry.push_back(surfaceInfo);

    unsigned int width, height;
    tbufInfo bufferInfo1 ;
    bufferInfo1.buffer = PasManager::GetInstance()->m_pCarBuffer;
    bufferInfo1.width = 152;
    bufferInfo1.height = 228;
    bufferInfo1.bRender = TRUE;
    renderData1.bufferMap.insert(make_pair(ADAS_PAS_CAR_STATUS, bufferInfo1));


    tbufInfo DefaultAreabufferInfo;
    DefaultAreabufferInfo.buffer = PasManager::GetInstance()->m_pHasCompoundedArea;
    DefaultAreabufferInfo.width = 152;
    DefaultAreabufferInfo.height = 228;
    DefaultAreabufferInfo.bRender = TRUE;
    renderData1.bufferMap.insert(make_pair(ADAS_PAS_RADAR_STATUS, DefaultAreabufferInfo));

    tbufInfo BackGroundbufferInfo;
    BackGroundbufferInfo.buffer = PasManager::GetInstance()->m_pHasCompoundedBackGround;
    BackGroundbufferInfo.width = 640;
    BackGroundbufferInfo.height = 720;
    BackGroundbufferInfo.bRender = TRUE;
    renderData1.bufferMap.insert(make_pair(ADAS_PAS_WARNING_STATUS, BackGroundbufferInfo));

    graphic = new CAdasGraphic();
}

GraphicVPAFord::~GraphicVPAFord()
{
    PasManager::DelInstance();
}

bool GraphicVPAFord::vInit(int screenWidth, int screenHeight)
{
    setscSize(screenWidth,screenHeight);
	return false;
}

VOID GraphicVPAFord::init()
{
    graphic->createSurface(surfaceArry);
}

void GraphicVPAFord::update()
{
    //-------------------------------------FrontLeftInside 2 degree

    PasManager::GetInstance()->m_pFrontLeftInside->Flush(2);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontLeftInside->Flush(1);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontLeftInside->Flush(2);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontLeftInside->Flush(3);  // > 2 degree ,highlight nothing
    graphic->Render(renderData1);
    sleep(1);

    //-------------------------------------------FrontLeft 3 degree

    PasManager::GetInstance()->m_pFrontLeft->Flush(3);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontLeft->Flush(2);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontLeft->Flush(1);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontLeft->Flush(2);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontLeft->Flush(3);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontLeft->Flush(4);  // > 3 degree ,highlight nothing
    graphic->Render(renderData1);
    sleep(1);


    //-------------------------------------------------FrontRight 3 degree

    PasManager::GetInstance()->m_pFrontRight->Flush(3);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontRight->Flush(2);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontRight->Flush(1);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontRight->Flush(2);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontRight->Flush(3);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontRight->Flush(4);  // > 3 degree ,highlight nothing
    graphic->Render(renderData1);
    sleep(1);



    //--------------------------------------------FrontRightInside 2 degree

    PasManager::GetInstance()->m_pFrontRightInside->Flush(2);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontRightInside->Flush(1);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontRightInside->Flush(2);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pFrontRightInside->Flush(3); // > 2 degree ,highlight nothing
    graphic->Render(renderData1);
    sleep(1);



    //----------------------------------------------RearLeftInside 3 degree

    PasManager::GetInstance()->m_pRearLeftInside->Flush(3);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeftInside->Flush(2);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeftInside->Flush(1);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeftInside->Flush(2);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeftInside->Flush(3);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeftInside->Flush(4); // > 3 degree ,highlight nothing
    graphic->Render(renderData1);
    sleep(1);


    //-------------------------------------------RearLeft  6 degree

    PasManager::GetInstance()->m_pRearLeft->Flush(6);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeft->Flush(5);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeft->Flush(4);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeft->Flush(3);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeft->Flush(2);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeft->Flush(1);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeft->Flush(2);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeft->Flush(3);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeft->Flush(4);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeft->Flush(5);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeft->Flush(6);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearLeft->Flush(7);  // > 6 degree ,highlight nothing
    graphic->Render(renderData1);
    sleep(1);

    //-------------------------------------------------RearRight  6 degree

    PasManager::GetInstance()->m_pRearRight->Flush(6);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRight->Flush(5);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRight->Flush(4);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRight->Flush(3);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRight->Flush(2);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRight->Flush(1);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRight->Flush(2);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRight->Flush(3);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRight->Flush(4);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRight->Flush(5);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRight->Flush(6);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRight->Flush(7);  // > 6 degree ,highlight nothing
    graphic->Render(renderData1);
    sleep(1);


    //----------------------------------------------RearRightInside 3 degree

    PasManager::GetInstance()->m_pRearRightInside->Flush(3);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRightInside->Flush(2);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRightInside->Flush(1);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRightInside->Flush(2);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRightInside->Flush(3);
    graphic->Render(renderData1);
    sleep(1);

    PasManager::GetInstance()->m_pRearRightInside->Flush(4);  // > 3 degree ,highlight nothing
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