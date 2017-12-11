
#include "ADASManager/PAS/FrontLeft.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

#include "./Res/pdc_front_left_1.h"
#include "./Res/pdc_front_left_2.h"
#include "./Res/pdc_front_left_3.h"
#include "./Res/pdc_front_left_4.h"
#include "./Res/pdc_front_left_5.h"
#include "./Res/pdc_front_left_6.h"
#include "./Res/pdc_front_left_7.h"
#include "./Res/pdc_front_left_8.h"
#include "./Res/pdc_front_left_9.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

FrontLeft::FrontLeft(const string& radarSenserName, BYTE* const hasCompoundedArea)
    : RadarSenser(radarSenserName)
{
    m_vColorBlockArray.push_back(nullptr);
    m_vColorBlockArray.push_back(new FrontLeftOneStep(FRONT_LEFT_ONE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontLeftTwoStep(FRONT_LEFT_TWO_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontLeftThreeStep(FRONT_LEFT_THREE_STEP, hasCompoundedArea));

    m_vColorBlockArray.push_back(new FrontLeftFourStep(FRONT_LEFT_FOUR_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontLeftFiveStep(FRONT_LEFT_FIVE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontLeftSixStep(FRONT_LEFT_SIX_STEP, hasCompoundedArea));

    m_vColorBlockArray.push_back(new FrontLeftSevenStep(FRONT_LEFT_SEVEN_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontLeftEightStep(FRONT_LEFT_EIGHT_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontLeftNineStep(FRONT_LEFT_NINE_STEP, hasCompoundedArea));
}

FrontLeft::~FrontLeft()
{
    for(auto val : m_vColorBlockArray) {
        delete val;
    }
}

FrontLeftOneStep::FrontLeftOneStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_left_1))
{
    GET_PNG_ARGS(pdc_front_left_1)
}

FrontLeftTwoStep::FrontLeftTwoStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_left_2))
{
    GET_PNG_ARGS(pdc_front_left_2)
}

FrontLeftThreeStep::FrontLeftThreeStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_left_3))
{
    GET_PNG_ARGS(pdc_front_left_3)
}

FrontLeftFourStep::FrontLeftFourStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_left_4))
{
    GET_PNG_ARGS(pdc_front_left_4)
}

FrontLeftFiveStep::FrontLeftFiveStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_left_5))
{
    GET_PNG_ARGS(pdc_front_left_5)
}

FrontLeftSixStep::FrontLeftSixStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_left_6))
{
    GET_PNG_ARGS(pdc_front_left_6)
}

FrontLeftSevenStep::FrontLeftSevenStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_left_7))
{
    GET_PNG_ARGS(pdc_front_left_7)
}

FrontLeftEightStep::FrontLeftEightStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_left_8))
{
    GET_PNG_ARGS(pdc_front_left_8)
}

FrontLeftNineStep::FrontLeftNineStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_left_9))
{
    GET_PNG_ARGS(pdc_front_left_9)
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman