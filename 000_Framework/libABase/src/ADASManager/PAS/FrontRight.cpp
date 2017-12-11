
#include "ADASManager/PAS/FrontRight.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

#include "./Res/pdc_front_right_1.h"
#include "./Res/pdc_front_right_2.h"
#include "./Res/pdc_front_right_3.h"
#include "./Res/pdc_front_right_4.h"
#include "./Res/pdc_front_right_5.h"
#include "./Res/pdc_front_right_6.h"
#include "./Res/pdc_front_right_7.h"
#include "./Res/pdc_front_right_8.h"
#include "./Res/pdc_front_right_9.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

FrontRight::FrontRight(const string& radarSenserName, BYTE* const hasCompoundedArea)
    : RadarSenser(radarSenserName)
{
    m_vColorBlockArray.push_back(nullptr);
    m_vColorBlockArray.push_back(new FrontRightOneStep(FRONT_RIGHT_ONE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontRightTwoStep(FRONT_RIGHT_TWO_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontRightThreeStep(FRONT_RIGHT_THREE_STEP, hasCompoundedArea));

    m_vColorBlockArray.push_back(new FrontRightFourStep(FRONT_RIGHT_FOUR_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontRightFiveStep(FRONT_RIGHT_FIVE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontRightSixStep(FRONT_RIGHT_SIX_STEP, hasCompoundedArea));

    m_vColorBlockArray.push_back(new FrontRightSevenStep(FRONT_RIGHT_SEVEN_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontRightEightStep(FRONT_RIGHT_EIGHT_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontRightNineStep(FRONT_RIGHT_NINE_STEP, hasCompoundedArea));
}

FrontRight::~FrontRight()
{
    for(auto val : m_vColorBlockArray) {
        delete val;
    }
}

FrontRightOneStep::FrontRightOneStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_right_1))
{
    GET_PNG_ARGS(pdc_front_right_1)
}

FrontRightTwoStep::FrontRightTwoStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_right_2))
{
    GET_PNG_ARGS(pdc_front_right_2)
}

FrontRightThreeStep::FrontRightThreeStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_right_3))
{
    GET_PNG_ARGS(pdc_front_right_3)
}

FrontRightFourStep::FrontRightFourStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_right_4))
{
    GET_PNG_ARGS(pdc_front_right_4)
}

FrontRightFiveStep::FrontRightFiveStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_right_5))
{
    GET_PNG_ARGS(pdc_front_right_5)
}

FrontRightSixStep::FrontRightSixStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_right_6))
{
    GET_PNG_ARGS(pdc_front_right_6)
}

FrontRightSevenStep::FrontRightSevenStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_right_7))
{
    GET_PNG_ARGS(pdc_front_right_7)
}

FrontRightEightStep::FrontRightEightStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_right_8))
{
    GET_PNG_ARGS(pdc_front_right_8)
}

FrontRightNineStep::FrontRightNineStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_right_9))
{
    GET_PNG_ARGS(pdc_front_right_9)
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman