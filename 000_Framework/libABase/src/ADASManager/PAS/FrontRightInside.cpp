
#include "ADASManager/PAS/FrontRightInside.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

#include "./Res/pdc_front_right_inside_0.h"
#include "./Res/pdc_front_right_inside_1.h"
#include "./Res/pdc_front_right_inside_2.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

FrontRightInside::FrontRightInside(const string& radarSenserName, BYTE* hasCompoundedArea)
    : RadarSenser(radarSenserName)
{
    m_vColorBlockArray.push_back(new FrontRightInsideDefault(FRONT_RIGHT_INSIDE_DEFAULT, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontRightInsideOneStep(FRONT_RIGHT_INSIDE_ONE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontRightInsideTwoStep(FRONT_RIGHT_INSIDE_TWO_STEP, hasCompoundedArea));
}

FrontRightInside::~FrontRightInside()
{
    for(auto val : m_vColorBlockArray) {
        delete val;
    }
}

FrontRightInsideDefault::FrontRightInsideDefault(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_front_right_inside_0PngResource.length;
    m_uiWidth = pdc_front_right_inside_0PngResource.width;
    m_uiHight = pdc_front_right_inside_0PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_front_right_inside_0PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_front_right_inside_0PngResource.endIndex;
    m_pColorBlockBuffer = pdc_front_right_inside_0PngResource.uClsinfo;

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void FrontRightInsideDefault::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void FrontRightInsideDefault::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

FrontRightInsideOneStep::FrontRightInsideOneStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_front_right_inside_1PngResource.length;
    m_uiWidth = pdc_front_right_inside_1PngResource.width;
    m_uiHight = pdc_front_right_inside_1PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_front_right_inside_1PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_front_right_inside_1PngResource.endIndex;
    m_pColorBlockBuffer = pdc_front_right_inside_1PngResource.uClsinfo;

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void FrontRightInsideOneStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void FrontRightInsideOneStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

FrontRightInsideTwoStep::FrontRightInsideTwoStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_front_right_inside_2PngResource.length;
    m_uiWidth = pdc_front_right_inside_2PngResource.width;
    m_uiHight = pdc_front_right_inside_2PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_front_right_inside_2PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_front_right_inside_2PngResource.endIndex;
    m_pColorBlockBuffer = pdc_front_right_inside_2PngResource.uClsinfo;

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void FrontRightInsideTwoStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void FrontRightInsideTwoStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman