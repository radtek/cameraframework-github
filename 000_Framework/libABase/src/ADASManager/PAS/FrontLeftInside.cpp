
#include "ADASManager/PAS/FrontLeftInside.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

#include "./Res/pdc_front_left_inside_0.h"
#include "./Res/pdc_front_left_inside_1.h"
#include "./Res/pdc_front_left_inside_2.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

FrontLeftInside::FrontLeftInside(const string& radarSenserName, BYTE* hasCompoundedArea)
    : RadarSenser(radarSenserName)
{
    m_vColorBlockArray.push_back(new FrontLeftInsideDefault(FRONT_LEFT_INSIDE_DEFAULT, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontLeftInsideOneStep(FRONT_LEFT_INSIDE_ONE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontLeftInsideTwoStep(FRONT_LEFT_INSIDE_TWO_STEP, hasCompoundedArea));
}

FrontLeftInside::~FrontLeftInside()
{
    for(auto val : m_vColorBlockArray) {
        delete val;
    }
}

FrontLeftInsideDefault::FrontLeftInsideDefault(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_front_left_inside_0PngResource.length;
    m_uiWidth = pdc_front_left_inside_0PngResource.width;
    m_uiHight = pdc_front_left_inside_0PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_front_left_inside_0PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_front_left_inside_0PngResource.endIndex;
    m_pColorBlockBuffer = const_cast<BYTE*>(pdc_front_left_inside_0PngResource.uClsinfo);

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void FrontLeftInsideDefault::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void FrontLeftInsideDefault::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

FrontLeftInsideOneStep::FrontLeftInsideOneStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_front_left_inside_1PngResource.length;
    m_uiWidth = pdc_front_left_inside_1PngResource.width;
    m_uiHight = pdc_front_left_inside_1PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_front_left_inside_1PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_front_left_inside_1PngResource.endIndex;
    m_pColorBlockBuffer = const_cast<BYTE*>(pdc_front_left_inside_1PngResource.uClsinfo);

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void FrontLeftInsideOneStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void FrontLeftInsideOneStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

FrontLeftInsideTwoStep::FrontLeftInsideTwoStep(const string& pngResourceFile, BYTE* hasCompoundedArea)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_front_left_inside_2PngResource.length;
    m_uiWidth = pdc_front_left_inside_2PngResource.width;
    m_uiHight = pdc_front_left_inside_2PngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_front_left_inside_2PngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_front_left_inside_2PngResource.endIndex;
    m_pColorBlockBuffer = const_cast<BYTE*>(pdc_front_left_inside_2PngResource.uClsinfo);

    m_HasCompoundedAreaHolder = hasCompoundedArea;
}

void FrontLeftInsideTwoStep::CompoundArea()
{
    ColorBlock::CompoundArea();
}

void FrontLeftInsideTwoStep::DeCompoundArea()
{
    ColorBlock::DeCompoundArea();
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman