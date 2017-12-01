
#include "ADASManager/PAS/RearRightInside.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

#include "./Res/pdc_rear_right_inside_0.h"
#include "./Res/pdc_rear_right_inside_1.h"
#include "./Res/pdc_rear_right_inside_2.h"
#include "./Res/pdc_rear_right_inside_3.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

RearRightInside::RearRightInside(const string& radarSenserName, BYTE* hasCompoundedArea)
    : RadarSenser(radarSenserName)
{
    m_vColorBlockArray.push_back(new RearRightInsideDefault(REAR_RIGHT_INSIDE_DEFAULT, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearRightInsideOneStep(REAR_RIGHT_INSIDE_ONE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearRightInsideTwoStep(REAR_RIGHT_INSIDE_TWO_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearRightInsideThreeStep(REAR_RIGHT_INSIDE_THREE_STEP, hasCompoundedArea));
}

RearRightInside::~RearRightInside()
{
    for(auto val : m_vColorBlockArray) {
        delete val;
    }
}

RearRightInsideDefault::RearRightInsideDefault(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_rear_right_inside_0PngResource.length;
    m_uiWidth = pdc_rear_right_inside_0PngResource.width;
    m_uiHight = pdc_rear_right_inside_0PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_rear_right_inside_0PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_rear_right_inside_0PngResource.endIndex;
    m_pColorBlockBuffer = pdc_rear_right_inside_0PngResource.uClsinfo;

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void RearRightInsideDefault::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void RearRightInsideDefault::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

RearRightInsideOneStep::RearRightInsideOneStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_rear_right_inside_1PngResource.length;
    m_uiWidth = pdc_rear_right_inside_1PngResource.width;
    m_uiHight = pdc_rear_right_inside_1PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_rear_right_inside_1PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_rear_right_inside_1PngResource.endIndex;
    m_pColorBlockBuffer = pdc_rear_right_inside_1PngResource.uClsinfo;

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void RearRightInsideOneStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void RearRightInsideOneStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

RearRightInsideTwoStep::RearRightInsideTwoStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_rear_right_inside_2PngResource.length;
    m_uiWidth = pdc_rear_right_inside_2PngResource.width;
    m_uiHight = pdc_rear_right_inside_2PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_rear_right_inside_2PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_rear_right_inside_2PngResource.endIndex;
    m_pColorBlockBuffer = pdc_rear_right_inside_2PngResource.uClsinfo;

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void RearRightInsideTwoStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void RearRightInsideTwoStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

RearRightInsideThreeStep::RearRightInsideThreeStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_rear_right_inside_3PngResource.length;
    m_uiWidth = pdc_rear_right_inside_3PngResource.width;
    m_uiHight = pdc_rear_right_inside_3PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_rear_right_inside_3PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_rear_right_inside_3PngResource.endIndex;
    m_pColorBlockBuffer = pdc_rear_right_inside_3PngResource.uClsinfo;

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void RearRightInsideThreeStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void RearRightInsideThreeStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman