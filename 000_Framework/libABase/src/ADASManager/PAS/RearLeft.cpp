
#include "ADASManager/PAS/RearLeft.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

#include "./Res/pdc_rear_left_1.h"
#include "./Res/pdc_rear_left_2.h"
#include "./Res/pdc_rear_left_3.h"
#include "./Res/pdc_rear_left_4.h"
#include "./Res/pdc_rear_left_5.h"
#include "./Res/pdc_rear_left_6.h"
#include "./Res/pdc_rear_left_7.h"
#include "./Res/pdc_rear_left_8.h"
#include "./Res/pdc_rear_left_9.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

RearLeft::RearLeft(const string& radarSenserName, BYTE* const hasCompoundedArea)
    : RadarSenser(radarSenserName)
{
    m_vColorBlockArray.push_back(nullptr);
    m_vColorBlockArray.push_back(new RearLeftOneStep(REAR_LEFT_ONE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearLeftTwoStep(REAR_LEFT_TWO_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearLeftThreeStep(REAR_LEFT_THREE_STEP, hasCompoundedArea));

    m_vColorBlockArray.push_back(new RearLeftFourStep(REAR_LEFT_FOUR_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearLeftFiveStep(REAR_LEFT_FIVE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearLeftSixStep(REAR_LEFT_SIX_STEP, hasCompoundedArea));

    m_vColorBlockArray.push_back(new RearLeftSevenStep(REAR_LEFT_SEVEN_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearLeftEightStep(REAR_LEFT_EIGHT_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new RearLeftNineStep(REAR_LEFT_NINE_STEP, hasCompoundedArea));
}

RearLeft::~RearLeft()
{
    for(auto val : m_vColorBlockArray) {
        delete val;
    }
}

RearLeftOneStep::RearLeftOneStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_left_1))
{
    GET_PNG_ARGS(pdc_rear_left_1)
}

RearLeftTwoStep::RearLeftTwoStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_left_2))
{
    GET_PNG_ARGS(pdc_rear_left_2)
}

RearLeftThreeStep::RearLeftThreeStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_left_3))
{
    GET_PNG_ARGS(pdc_rear_left_3)
}

RearLeftFourStep::RearLeftFourStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_left_4))
{
    GET_PNG_ARGS(pdc_rear_left_4)
}

RearLeftFiveStep::RearLeftFiveStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_left_5))
{
    GET_PNG_ARGS(pdc_rear_left_5)
}

RearLeftSixStep::RearLeftSixStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_left_6))
{
    GET_PNG_ARGS(pdc_rear_left_6)
}

RearLeftSevenStep::RearLeftSevenStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_left_7))
{
    GET_PNG_ARGS(pdc_rear_left_7)
}

RearLeftEightStep::RearLeftEightStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_left_8))
{
    GET_PNG_ARGS(pdc_rear_left_8)
}

RearLeftNineStep::RearLeftNineStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_rear_left_9))
{
    GET_PNG_ARGS(pdc_rear_left_9)
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman