
#include "ADASManager/PAS/RearRight.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

#include "./Res/pdc_rear_right_1.h"
#include "./Res/pdc_rear_right_2.h"
#include "./Res/pdc_rear_right_3.h"
#include "./Res/pdc_rear_right_4.h"
#include "./Res/pdc_rear_right_5.h"
#include "./Res/pdc_rear_right_6.h"
#include "./Res/pdc_rear_right_7.h"
#include "./Res/pdc_rear_right_8.h"
#include "./Res/pdc_rear_right_9.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

RearRight::RearRight(const string& radarSenserName, BYTE* const hasCompoundedArea)
    : RadarSenser(radarSenserName)
{
    m_vColorBlockArray.push_back(nullptr);
    m_vColorBlockArray.push_back(new RearRightOneStep(REAR_RIGHT_ONE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearRightTwoStep(REAR_RIGHT_TWO_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearRightThreeStep(REAR_RIGHT_THREE_STEP, hasCompoundedArea));

    m_vColorBlockArray.push_back(new RearRightFourStep(REAR_RIGHT_FOUR_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearRightFiveStep(REAR_RIGHT_FIVE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearRightSixStep(REAR_RIGHT_SIX_STEP, hasCompoundedArea));

    m_vColorBlockArray.push_back(new RearRightSevenStep(REAR_RIGHT_SEVEN_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearRightEightStep(REAR_RIGHT_EIGHT_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearRightNineStep(REAR_RIGHT_NINE_STEP, hasCompoundedArea));
}

RearRight::~RearRight()
{
    for(auto val : m_vColorBlockArray) {
        delete val;
    }
}

RearRightOneStep::RearRightOneStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_right_1))
{
    GET_PNG_ARGS(pdc_rear_right_1)
}

RearRightTwoStep::RearRightTwoStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_right_2))
{
    GET_PNG_ARGS(pdc_rear_right_2)
}

RearRightThreeStep::RearRightThreeStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_right_3))
{
    GET_PNG_ARGS(pdc_rear_right_3)
}

RearRightFourStep::RearRightFourStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_right_4))
{
    GET_PNG_ARGS(pdc_rear_right_4)
}

RearRightFiveStep::RearRightFiveStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_right_5))
{
    GET_PNG_ARGS(pdc_rear_right_5)
}

RearRightSixStep::RearRightSixStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_right_6))
{
    GET_PNG_ARGS(pdc_rear_right_6)
}

RearRightSevenStep::RearRightSevenStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_right_7))
{
    GET_PNG_ARGS(pdc_rear_right_7)
}

RearRightEightStep::RearRightEightStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_right_8))
{
    GET_PNG_ARGS(pdc_rear_right_8)
}

RearRightNineStep::RearRightNineStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_right_9))
{
    GET_PNG_ARGS(pdc_rear_right_9)
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman