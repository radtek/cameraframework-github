
#include "ADASManager/PAS/RearRightInside.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

#include "./Res/pdc_rear_right_inside_1.h"
#include "./Res/pdc_rear_right_inside_2.h"
#include "./Res/pdc_rear_right_inside_3.h"
#include "./Res/pdc_rear_right_inside_4.h"
#include "./Res/pdc_rear_right_inside_5.h"
#include "./Res/pdc_rear_right_inside_6.h"
#include "./Res/pdc_rear_right_inside_7.h"
#include "./Res/pdc_rear_right_inside_8.h"
#include "./Res/pdc_rear_right_inside_9.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

RearRightInside::RearRightInside(const string& radarSenserName, BYTE* const hasCompoundedArea)
    : RadarSenser(radarSenserName)
{
    m_vColorBlockArray.push_back(nullptr);
    m_vColorBlockArray.push_back(new RearRightInsideOneStep(REAR_RIGHT_INSIDE_ONE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearRightInsideTwoStep(REAR_RIGHT_INSIDE_TWO_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearRightInsideThreeStep(REAR_RIGHT_INSIDE_THREE_STEP, hasCompoundedArea));

    m_vColorBlockArray.push_back(new RearRightInsideFourStep(REAR_RIGHT_INSIDE_FOUR_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearRightInsideFiveStep(REAR_RIGHT_INSIDE_FIVE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearRightInsideSixStep(REAR_RIGHT_INSIDE_SIX_STEP, hasCompoundedArea));

    m_vColorBlockArray.push_back(new RearRightInsideSevenStep(REAR_RIGHT_INSIDE_SEVEN_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearRightInsideEightStep(REAR_RIGHT_INSIDE_EIGHT_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearRightInsideNineStep(REAR_RIGHT_INSIDE_NINE_STEP, hasCompoundedArea));
}

RearRightInside::~RearRightInside()
{
    for(auto val : m_vColorBlockArray) {
        delete val;
    }
}

RearRightInsideOneStep::RearRightInsideOneStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile , hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_right_inside_1))
{
    GET_PNG_ARGS(pdc_rear_right_inside_1)
}

RearRightInsideTwoStep::RearRightInsideTwoStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile , hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_right_inside_2))
{
    GET_PNG_ARGS(pdc_rear_right_inside_2)
}

RearRightInsideThreeStep::RearRightInsideThreeStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile , hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_right_inside_3))
{
    GET_PNG_ARGS(pdc_rear_right_inside_3)
}

RearRightInsideFourStep::RearRightInsideFourStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile , hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_right_inside_4))
{
    GET_PNG_ARGS(pdc_rear_right_inside_4)
}

RearRightInsideFiveStep::RearRightInsideFiveStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile , hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_right_inside_5))
{
    GET_PNG_ARGS(pdc_rear_right_inside_5)
}

RearRightInsideSixStep::RearRightInsideSixStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile , hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_right_inside_6))
{
    GET_PNG_ARGS(pdc_rear_right_inside_6)
}

RearRightInsideSevenStep::RearRightInsideSevenStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile , hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_right_inside_7))
{
    GET_PNG_ARGS(pdc_rear_right_inside_7)
}

RearRightInsideEightStep::RearRightInsideEightStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile , hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_right_inside_8))
{
    GET_PNG_ARGS(pdc_rear_right_inside_8)
}

RearRightInsideNineStep::RearRightInsideNineStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile , hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_right_inside_9))
{
    GET_PNG_ARGS(pdc_rear_right_inside_9)
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman