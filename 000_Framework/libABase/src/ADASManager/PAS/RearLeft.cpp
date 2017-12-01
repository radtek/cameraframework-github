
#include "ADASManager/PAS/RearLeft.h"
#include "ADASManager/PAS/ResourcePngDefine.h"
#include "ADASManager/PAS/GraphicCore/PasUtils.h"

#include "./Res/pdc_rear_left_0.h"
#include "./Res/pdc_rear_left_1.h"
#include "./Res/pdc_rear_left_2.h"
#include "./Res/pdc_rear_left_3.h"
#include "./Res/pdc_rear_left_4.h"
#include "./Res/pdc_rear_left_5.h"
#include "./Res/pdc_rear_left_6.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

RearLeft::RearLeft(const string& radarSenserName, BYTE* hasCompoundedArea)
    : RadarSenser(radarSenserName)
{
    m_vColorBlockArray.push_back(new RearLeftDefault(REAR_LEFT_DEFAULT, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearLeftOneStep(REAR_LEFT_ONE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearLeftTwoStep(REAR_LEFT_TWO_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearLeftThreeStep(REAR_LEFT_THREE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearLeftFourStep(REAR_LEFT_FOUR_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearLeftFiveStep(REAR_LEFT_FIVE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearLeftSixStep(REAR_LEFT_SIX_STEP, hasCompoundedArea));
}

RearLeft::~RearLeft()
{
    for(auto val : m_vColorBlockArray) {
        delete val;
    }
}

RearLeftDefault::RearLeftDefault(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_rear_left_0PngResource.length;
    m_uiWidth = pdc_rear_left_0PngResource.width;
    m_uiHight = pdc_rear_left_0PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_rear_left_0PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_rear_left_0PngResource.endIndex;
    m_pColorBlockBuffer = pdc_rear_left_0PngResource.uClsinfo;

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void RearLeftDefault::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void RearLeftDefault::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

RearLeftOneStep::RearLeftOneStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_rear_left_1PngResource.length;
    m_uiWidth = pdc_rear_left_1PngResource.width;
    m_uiHight = pdc_rear_left_1PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_rear_left_1PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_rear_left_1PngResource.endIndex;
    m_pColorBlockBuffer = pdc_rear_left_1PngResource.uClsinfo;

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void RearLeftOneStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void RearLeftOneStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

RearLeftTwoStep::RearLeftTwoStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_rear_left_2PngResource.length;
    m_uiWidth = pdc_rear_left_2PngResource.width;
    m_uiHight = pdc_rear_left_2PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_rear_left_2PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_rear_left_2PngResource.endIndex;
    m_pColorBlockBuffer = pdc_rear_left_2PngResource.uClsinfo;

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void RearLeftTwoStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void RearLeftTwoStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

RearLeftThreeStep::RearLeftThreeStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_rear_left_3PngResource.length;
    m_uiWidth = pdc_rear_left_3PngResource.width;
    m_uiHight = pdc_rear_left_3PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_rear_left_3PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_rear_left_3PngResource.endIndex;
    m_pColorBlockBuffer = pdc_rear_left_3PngResource.uClsinfo;

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void RearLeftThreeStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void RearLeftThreeStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

RearLeftFourStep::RearLeftFourStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_rear_left_4PngResource.length;
    m_uiWidth = pdc_rear_left_4PngResource.width;
    m_uiHight = pdc_rear_left_4PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_rear_left_4PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_rear_left_4PngResource.endIndex;
    m_pColorBlockBuffer = pdc_rear_left_4PngResource.uClsinfo;

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void RearLeftFourStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void RearLeftFourStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

RearLeftFiveStep::RearLeftFiveStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_rear_left_5PngResource.length;
    m_uiWidth = pdc_rear_left_5PngResource.width;
    m_uiHight = pdc_rear_left_5PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_rear_left_5PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_rear_left_5PngResource.endIndex;
    m_pColorBlockBuffer = pdc_rear_left_5PngResource.uClsinfo;

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void RearLeftFiveStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void RearLeftFiveStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

RearLeftSixStep::RearLeftSixStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_rear_left_6PngResource.length;
    m_uiWidth = pdc_rear_left_6PngResource.width;
    m_uiHight = pdc_rear_left_6PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_rear_left_6PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_rear_left_6PngResource.endIndex;
    m_pColorBlockBuffer = pdc_rear_left_6PngResource.uClsinfo;

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void RearLeftSixStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void RearLeftSixStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman