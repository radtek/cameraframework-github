
#include "ADASManager/PAS/FrontRightInside.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

#include "./Res/pdc_front_right_inside_1.h"
#include "./Res/pdc_front_right_inside_2.h"
#include "./Res/pdc_front_right_inside_3.h"
#include "./Res/pdc_front_right_inside_4.h"
#include "./Res/pdc_front_right_inside_5.h"
#include "./Res/pdc_front_right_inside_6.h"
#include "./Res/pdc_front_right_inside_7.h"
#include "./Res/pdc_front_right_inside_8.h"
#include "./Res/pdc_front_right_inside_9.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

FrontRightInside::FrontRightInside(const string& radarSenserName, BYTE* const hasCompoundedArea)
    : RadarSenser(radarSenserName)
{
    m_vColorBlockArray.push_back(nullptr);
    m_vColorBlockArray.push_back(new FrontRightInsideOneStep(FRONT_RIGHT_INSIDE_ONE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontRightInsideTwoStep(FRONT_RIGHT_INSIDE_TWO_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontRightInsideThreeStep(FRONT_RIGHT_INSIDE_THREE_STEP, hasCompoundedArea));

    m_vColorBlockArray.push_back(new FrontRightInsideFourStep(FRONT_RIGHT_INSIDE_FOUR_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontRightInsideFiveStep(FRONT_RIGHT_INSIDE_FIVE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontRightInsideSixStep(FRONT_RIGHT_INSIDE_SIX_STEP, hasCompoundedArea));

    m_vColorBlockArray.push_back(new FrontRightInsideSevenStep(FRONT_RIGHT_INSIDE_SEVEN_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontRightInsideEightStep(FRONT_RIGHT_INSIDE_EIGHT_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontRightInsideNineStep(FRONT_RIGHT_INSIDE_NINE_STEP, hasCompoundedArea));
}

FrontRightInside::~FrontRightInside()
{
    for(auto val : m_vColorBlockArray) {
        delete val;
    }
}

FrontRightInsideOneStep::FrontRightInsideOneStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_right_inside_1))
{
    GET_PNG_ARGS(pdc_front_right_inside_1)
}

FrontRightInsideTwoStep::FrontRightInsideTwoStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_right_inside_2))
{
    GET_PNG_ARGS(pdc_front_right_inside_2)
}

FrontRightInsideThreeStep::FrontRightInsideThreeStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_right_inside_3))
{
    GET_PNG_ARGS(pdc_front_right_inside_3)
}

FrontRightInsideFourStep::FrontRightInsideFourStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_right_inside_4))
{
    GET_PNG_ARGS(pdc_front_right_inside_4)
}

FrontRightInsideFiveStep::FrontRightInsideFiveStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_right_inside_5))
{
    GET_PNG_ARGS(pdc_front_right_inside_5)
}

FrontRightInsideSixStep::FrontRightInsideSixStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_right_inside_6))
{
    GET_PNG_ARGS(pdc_front_right_inside_6)
}

FrontRightInsideSevenStep::FrontRightInsideSevenStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_right_inside_7))
{
    GET_PNG_ARGS(pdc_front_right_inside_7)
}

FrontRightInsideEightStep::FrontRightInsideEightStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_right_inside_8))
{
    GET_PNG_ARGS(pdc_front_right_inside_8)
}

FrontRightInsideNineStep::FrontRightInsideNineStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_right_inside_9))
{
    GET_PNG_ARGS(pdc_front_right_inside_9)
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman