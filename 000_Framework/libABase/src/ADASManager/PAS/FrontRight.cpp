
#include "ADASManager/PAS/FrontRight.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

#include "./Res/pdc_front_right_0.h"
#include "./Res/pdc_front_right_1.h"
#include "./Res/pdc_front_right_2.h"
#include "./Res/pdc_front_right_3.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

FrontRight::FrontRight(const string& radarSenserName, BYTE* hasCompoundedArea)
    : RadarSenser(radarSenserName)
{
    m_vColorBlockArray.push_back(new FrontRightDefault(FRONT_RIGHT_DEFAULT, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontRightOneStep(FRONT_RIGHT_ONE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontRightTwoStep(FRONT_RIGHT_TWO_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontRightThreeStep(FRONT_RIGHT_THREE_STEP, hasCompoundedArea));
}

FrontRight::~FrontRight()
{
    for(auto val : m_vColorBlockArray) {
        delete val;
    }
}

FrontRightDefault::FrontRightDefault(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_front_right_0PngResource.length;
    m_uiWidth = pdc_front_right_0PngResource.width;
    m_uiHight = pdc_front_right_0PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_front_right_0PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_front_right_0PngResource.endIndex;
    m_pColorBlockBuffer = const_cast<BYTE*>(pdc_front_right_0PngResource.uClsinfo);

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void FrontRightDefault::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void FrontRightDefault::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

FrontRightOneStep::FrontRightOneStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_front_right_1PngResource.length;
    m_uiWidth = pdc_front_right_1PngResource.width;
    m_uiHight = pdc_front_right_1PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_front_right_1PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_front_right_1PngResource.endIndex;
    m_pColorBlockBuffer = const_cast<BYTE*>(pdc_front_right_1PngResource.uClsinfo);

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void FrontRightOneStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void FrontRightOneStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

FrontRightTwoStep::FrontRightTwoStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_front_right_2PngResource.length;
    m_uiWidth = pdc_front_right_2PngResource.width;
    m_uiHight = pdc_front_right_2PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_front_right_2PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_front_right_2PngResource.endIndex;
    m_pColorBlockBuffer = const_cast<BYTE*>(pdc_front_right_2PngResource.uClsinfo);

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void FrontRightTwoStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void FrontRightTwoStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

FrontRightThreeStep::FrontRightThreeStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_front_right_3PngResource.length;
    m_uiWidth = pdc_front_right_3PngResource.width;
    m_uiHight = pdc_front_right_3PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_front_right_3PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_front_right_3PngResource.endIndex;
    m_pColorBlockBuffer = const_cast<BYTE*>(pdc_front_right_3PngResource.uClsinfo);

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void FrontRightThreeStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void FrontRightThreeStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman