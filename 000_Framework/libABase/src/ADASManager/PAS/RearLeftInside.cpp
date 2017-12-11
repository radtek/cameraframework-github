
#include "ADASManager/PAS/RearLeftInside.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

#include "./Res/pdc_rear_left_inside_1.h"
#include "./Res/pdc_rear_left_inside_2.h"
#include "./Res/pdc_rear_left_inside_3.h"
#include "./Res/pdc_rear_left_inside_4.h"
#include "./Res/pdc_rear_left_inside_5.h"
#include "./Res/pdc_rear_left_inside_6.h"
#include "./Res/pdc_rear_left_inside_7.h"
#include "./Res/pdc_rear_left_inside_8.h"
#include "./Res/pdc_rear_left_inside_9.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

RearLeftInside::RearLeftInside(const string& radarSenserName, BYTE* const hasCompoundedArea)
    : RadarSenser(radarSenserName)
{
    m_vColorBlockArray.push_back(nullptr);
    m_vColorBlockArray.push_back(new RearLeftInsideOneStep(REAR_LEFT_INSIDE_ONE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearLeftInsideTwoStep(REAR_LEFT_INSIDE_TWO_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearLeftInsideThreeStep(REAR_LEFT_INSIDE_THREE_STEP, hasCompoundedArea));

    m_vColorBlockArray.push_back(new RearLeftInsideFourStep(REAR_LEFT_INSIDE_FOUR_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearLeftInsideFiveStep(REAR_LEFT_INSIDE_FIVE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearLeftInsideSixStep(REAR_LEFT_INSIDE_SIX_STEP, hasCompoundedArea));

    m_vColorBlockArray.push_back(new RearLeftInsideSevenStep(REAR_LEFT_INSIDE_SEVEN_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearLeftInsideEightStep(REAR_LEFT_INSIDE_EIGHT_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearLeftInsideNineStep(REAR_LEFT_INSIDE_NINE_STEP, hasCompoundedArea));
}

RearLeftInside::~RearLeftInside()
{
    for(auto val : m_vColorBlockArray) {
        delete val;
    }
}

RearLeftInsideOneStep::RearLeftInsideOneStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_left_inside_1))
{
    GET_PNG_ARGS(pdc_rear_left_inside_1)
}

RearLeftInsideTwoStep::RearLeftInsideTwoStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_left_inside_2))
{
    GET_PNG_ARGS(pdc_rear_left_inside_2)
}

RearLeftInsideThreeStep::RearLeftInsideThreeStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_left_inside_3))
{
    GET_PNG_ARGS(pdc_rear_left_inside_3)
}

RearLeftInsideFourStep::RearLeftInsideFourStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_left_inside_4))
{
    GET_PNG_ARGS(pdc_rear_left_inside_4)
}

RearLeftInsideFiveStep::RearLeftInsideFiveStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_left_inside_5))
{
    GET_PNG_ARGS(pdc_rear_left_inside_5)
}

RearLeftInsideSixStep::RearLeftInsideSixStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_left_inside_6))
{
    GET_PNG_ARGS(pdc_rear_left_inside_6)
}

RearLeftInsideSevenStep::RearLeftInsideSevenStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_left_inside_7))
{
    GET_PNG_ARGS(pdc_rear_left_inside_7)
}

RearLeftInsideEightStep::RearLeftInsideEightStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_left_inside_8))
{
    GET_PNG_ARGS(pdc_rear_left_inside_8)
}

RearLeftInsideNineStep::RearLeftInsideNineStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_left_inside_9))
{
    GET_PNG_ARGS(pdc_rear_left_inside_9)
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman