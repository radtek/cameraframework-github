
#include "ADASManager/PAS/RearRight.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

#include "./Res/pdc_rear_right_0.h"
#include "./Res/pdc_rear_right_1.h"
#include "./Res/pdc_rear_right_2.h"
#include "./Res/pdc_rear_right_3.h"
#include "./Res/pdc_rear_right_4.h"
#include "./Res/pdc_rear_right_5.h"
#include "./Res/pdc_rear_right_6.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

RearRight::RearRight(const string& radarSenserName, BYTE* hasCompoundedArea)
    : RadarSenser(radarSenserName)
{
    m_vColorBlockArray.push_back(new RearRightDefault(REAR_RIGHT_DEFAULT, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearRightOneStep(REAR_RIGHT_ONE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearRightTwoStep(REAR_RIGHT_TWO_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearRightThreeStep(REAR_RIGHT_THREE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearRightFourStep(REAR_RIGHT_FOUR_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearRightFiveStep(REAR_RIGHT_FIVE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearRightSixStep(REAR_RIGHT_SIX_STEP, hasCompoundedArea));
}

RearRight::~RearRight()
{
    for(auto val : m_vColorBlockArray) {
        delete val;
    }
}

RearRightDefault::RearRightDefault(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_rear_right_0PngResource.length;
    m_uiWidth = pdc_rear_right_0PngResource.width;
    m_uiHight = pdc_rear_right_0PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_rear_right_0PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_rear_right_0PngResource.endIndex;
    m_pColorBlockBuffer = pdc_rear_right_0PngResource.uClsinfo;

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void RearRightDefault::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void RearRightDefault::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

RearRightOneStep::RearRightOneStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_rear_right_1PngResource.length;
    m_uiWidth = pdc_rear_right_1PngResource.width;
    m_uiHight = pdc_rear_right_1PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_rear_right_1PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_rear_right_1PngResource.endIndex;
    m_pColorBlockBuffer = pdc_rear_right_1PngResource.uClsinfo;

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void RearRightOneStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void RearRightOneStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

RearRightTwoStep::RearRightTwoStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_rear_right_2PngResource.length;
    m_uiWidth = pdc_rear_right_2PngResource.width;
    m_uiHight = pdc_rear_right_2PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_rear_right_2PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_rear_right_2PngResource.endIndex;
    m_pColorBlockBuffer = pdc_rear_right_2PngResource.uClsinfo;

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void RearRightTwoStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void RearRightTwoStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

RearRightThreeStep::RearRightThreeStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_rear_right_3PngResource.length;
    m_uiWidth = pdc_rear_right_3PngResource.width;
    m_uiHight = pdc_rear_right_3PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_rear_right_3PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_rear_right_3PngResource.endIndex;
    m_pColorBlockBuffer = pdc_rear_right_3PngResource.uClsinfo;

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void RearRightThreeStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void RearRightThreeStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

RearRightFourStep::RearRightFourStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_rear_right_4PngResource.length;
    m_uiWidth = pdc_rear_right_4PngResource.width;
    m_uiHight = pdc_rear_right_4PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_rear_right_4PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_rear_right_4PngResource.endIndex;
    m_pColorBlockBuffer = pdc_rear_right_4PngResource.uClsinfo;

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void RearRightFourStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void RearRightFourStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

RearRightFiveStep::RearRightFiveStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_rear_right_5PngResource.length;
    m_uiWidth = pdc_rear_right_5PngResource.width;
    m_uiHight = pdc_rear_right_5PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_rear_right_5PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_rear_right_5PngResource.endIndex;
    m_pColorBlockBuffer = pdc_rear_right_5PngResource.uClsinfo;

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void RearRightFiveStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void RearRightFiveStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

RearRightSixStep::RearRightSixStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_rear_right_6PngResource.length;
    m_uiWidth = pdc_rear_right_6PngResource.width;
    m_uiHight = pdc_rear_right_6PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_rear_right_6PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_rear_right_6PngResource.endIndex;
    m_pColorBlockBuffer = pdc_rear_right_6PngResource.uClsinfo;

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void RearRightSixStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void RearRightSixStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman