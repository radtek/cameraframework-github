
#include "ADASManager/PAS/FrontLeftInside.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

#include "./Res/pdc_front_left_inside_1.h"
#include "./Res/pdc_front_left_inside_2.h"
#include "./Res/pdc_front_left_inside_3.h"
#include "./Res/pdc_front_left_inside_4.h"
#include "./Res/pdc_front_left_inside_5.h"
#include "./Res/pdc_front_left_inside_6.h"
#include "./Res/pdc_front_left_inside_7.h"
#include "./Res/pdc_front_left_inside_8.h"
#include "./Res/pdc_front_left_inside_9.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

FrontLeftInside::FrontLeftInside(const string& radarSenserName, BYTE* const hasCompoundedArea)
    : RadarSenser(radarSenserName)
{
    m_vColorBlockArray.push_back(nullptr);
    m_vColorBlockArray.push_back(new FrontLeftInsideOneStep(FRONT_LEFT_INSIDE_ONE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontLeftInsideTwoStep(FRONT_LEFT_INSIDE_TWO_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontLeftInsideThreeStep(FRONT_LEFT_INSIDE_THREE_STEP, hasCompoundedArea));

    m_vColorBlockArray.push_back(new FrontLeftInsideFourStep(FRONT_LEFT_INSIDE_FOUR_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontLeftInsideFiveStep(FRONT_LEFT_INSIDE_FIVE_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontLeftInsideSixStep(FRONT_LEFT_INSIDE_SIX_STEP, hasCompoundedArea));

    m_vColorBlockArray.push_back(new FrontLeftInsideSevenStep(FRONT_LEFT_INSIDE_SEVEN_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontLeftInsideEightStep(FRONT_LEFT_INSIDE_EIGHT_STEP, hasCompoundedArea));
    m_vColorBlockArray.push_back(new FrontLeftInsideNineStep(FRONT_LEFT_INSIDE_NINE_STEP, hasCompoundedArea));
}

FrontLeftInside::~FrontLeftInside()
{
    for(auto val : m_vColorBlockArray) {
        delete val;
    }
}

FrontLeftInsideOneStep::FrontLeftInsideOneStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_left_inside_1))
{
    GET_PNG_ARGS(pdc_front_left_inside_1)
}

FrontLeftInsideTwoStep::FrontLeftInsideTwoStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_left_inside_2))
{
    GET_PNG_ARGS(pdc_front_left_inside_2)
}

FrontLeftInsideThreeStep::FrontLeftInsideThreeStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_left_inside_3))
{
    GET_PNG_ARGS(pdc_front_left_inside_3)
}

FrontLeftInsideFourStep::FrontLeftInsideFourStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_left_inside_4))
{
    GET_PNG_ARGS(pdc_front_left_inside_4)
}

FrontLeftInsideFiveStep::FrontLeftInsideFiveStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_left_inside_5))
{
    GET_PNG_ARGS(pdc_front_left_inside_5)
}

FrontLeftInsideSixStep::FrontLeftInsideSixStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_left_inside_6))
{
    GET_PNG_ARGS(pdc_front_left_inside_6)
}

FrontLeftInsideSevenStep::FrontLeftInsideSevenStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_left_inside_7))
{
    GET_PNG_ARGS(pdc_front_left_inside_7)
}

FrontLeftInsideEightStep::FrontLeftInsideEightStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_left_inside_8))
{
    GET_PNG_ARGS(pdc_front_left_inside_8)
}

FrontLeftInsideNineStep::FrontLeftInsideNineStep(const string& pngResourceFile, BYTE* const hasCompoundedArea)
    : ColorBlock(pngResourceFile, hasCompoundedArea, GET_PNG_RESOURCE(pdc_front_left_inside_9))
{
    GET_PNG_ARGS(pdc_front_left_inside_9)
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman