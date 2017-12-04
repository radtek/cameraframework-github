
#include "ADASManager/PAS/FrontLeft.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

#include "./Res/pdc_front_left_0.h"
#include "./Res/pdc_front_left_1.h"
#include "./Res/pdc_front_left_2.h"
#include "./Res/pdc_front_left_3.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

FrontLeft::FrontLeft(const string& radarSenserName, BYTE* hasCompoundedArea)
    : RadarSenser(radarSenserName)
{
    m_vColorBlockArray.push_back(new FrontLeftDefault(FRONT_LEFT_DEFAULT, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontLeftOneStep(FRONT_LEFT_ONE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontLeftTwoStep(FRONT_LEFT_TWO_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontLeftThreeStep(FRONT_LEFT_THREE_STEP, hasCompoundedArea));
}

FrontLeft::~FrontLeft()
{
    for(auto val : m_vColorBlockArray) {
        delete val;
    }
}

FrontLeftDefault::FrontLeftDefault(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_front_left_0PngResource.length;
    m_uiWidth = pdc_front_left_0PngResource.width;
    m_uiHight = pdc_front_left_0PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_front_left_0PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_front_left_0PngResource.endIndex;
    m_pColorBlockBuffer = const_cast<BYTE*>(pdc_front_left_0PngResource.uClsinfo);

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void FrontLeftDefault::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void FrontLeftDefault::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

FrontLeftOneStep::FrontLeftOneStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_front_left_1PngResource.length;
    m_uiWidth = pdc_front_left_1PngResource.width;
    m_uiHight = pdc_front_left_1PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_front_left_1PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_front_left_1PngResource.endIndex;
    m_pColorBlockBuffer = const_cast<BYTE*>(pdc_front_left_1PngResource.uClsinfo);

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void FrontLeftOneStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void FrontLeftOneStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

FrontLeftTwoStep::FrontLeftTwoStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_front_left_2PngResource.length;
    m_uiWidth = pdc_front_left_2PngResource.width;
    m_uiHight = pdc_front_left_2PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_front_left_2PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_front_left_2PngResource.endIndex;
    m_pColorBlockBuffer = const_cast<BYTE*>(pdc_front_left_2PngResource.uClsinfo);

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void FrontLeftTwoStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void FrontLeftTwoStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

FrontLeftThreeStep::FrontLeftThreeStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_front_left_3PngResource.length;
    m_uiWidth = pdc_front_left_3PngResource.width;
    m_uiHight = pdc_front_left_3PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_front_left_3PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_front_left_3PngResource.endIndex;
    m_pColorBlockBuffer = const_cast<BYTE*>(pdc_front_left_3PngResource.uClsinfo);

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void FrontLeftThreeStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void FrontLeftThreeStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman