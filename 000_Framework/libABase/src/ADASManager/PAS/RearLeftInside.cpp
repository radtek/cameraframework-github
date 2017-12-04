
#include "ADASManager/PAS/RearLeftInside.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

#include "./Res/pdc_rear_left_inside_0.h"
#include "./Res/pdc_rear_left_inside_1.h"
#include "./Res/pdc_rear_left_inside_2.h"
#include "./Res/pdc_rear_left_inside_3.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

RearLeftInside::RearLeftInside(const string& radarSenserName, BYTE* hasCompoundedArea)
    : RadarSenser(radarSenserName)
{
    m_vColorBlockArray.push_back(new RearLeftInsideDefault(REAR_LEFT_INSIDE_DEFAULT, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearLeftInsideOneStep(REAR_LEFT_INSIDE_ONE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearLeftInsideTwoStep(REAR_LEFT_INSIDE_TWO_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearLeftInsideThreeStep(REAR_LEFT_INSIDE_THREE_STEP, hasCompoundedArea));
}

RearLeftInside::~RearLeftInside()
{
    for(auto val : m_vColorBlockArray) {
        delete val;
    }
}

RearLeftInsideDefault::RearLeftInsideDefault(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_rear_left_inside_0PngResource.length;
    m_uiWidth = pdc_rear_left_inside_0PngResource.width;
    m_uiHight = pdc_rear_left_inside_0PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_rear_left_inside_0PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_rear_left_inside_0PngResource.endIndex;
    m_pColorBlockBuffer = const_cast<BYTE*>(pdc_rear_left_inside_0PngResource.uClsinfo);

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void RearLeftInsideDefault::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void RearLeftInsideDefault::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

RearLeftInsideOneStep::RearLeftInsideOneStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_rear_left_inside_1PngResource.length;
    m_uiWidth = pdc_rear_left_inside_1PngResource.width;
    m_uiHight = pdc_rear_left_inside_1PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_rear_left_inside_1PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_rear_left_inside_1PngResource.endIndex;
    m_pColorBlockBuffer = const_cast<BYTE*>(pdc_rear_left_inside_1PngResource.uClsinfo);

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void RearLeftInsideOneStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void RearLeftInsideOneStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

RearLeftInsideTwoStep::RearLeftInsideTwoStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_rear_left_inside_2PngResource.length;
    m_uiWidth = pdc_rear_left_inside_2PngResource.width;
    m_uiHight = pdc_rear_left_inside_2PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_rear_left_inside_2PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_rear_left_inside_2PngResource.endIndex;
    m_pColorBlockBuffer = const_cast<BYTE*>(pdc_rear_left_inside_2PngResource.uClsinfo);

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void RearLeftInsideTwoStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void RearLeftInsideTwoStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

RearLeftInsideThreeStep::RearLeftInsideThreeStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_rear_left_inside_3PngResource.length;
    m_uiWidth = pdc_rear_left_inside_3PngResource.width;
    m_uiHight = pdc_rear_left_inside_3PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_rear_left_inside_3PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_rear_left_inside_3PngResource.endIndex;
    m_pColorBlockBuffer = const_cast<BYTE*>(pdc_rear_left_inside_3PngResource.uClsinfo);

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void RearLeftInsideThreeStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void RearLeftInsideThreeStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman