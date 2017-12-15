
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_RESOURCEPNGDEFINE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_RESOURCEPNGDEFINE_H__

#define GET_PNG_ARGS(FILE) \
    m_uiLength = FILE##PngResource.length; \
    m_uiWidth = FILE##PngResource.width; \
    m_uiHight = FILE##PngResource.hight; \
    m_ValidDataArea.beginX =  FILE##PngResource.beginX; \
    m_ValidDataArea.beginY = FILE##PngResource.beginY; \
    m_ValidDataArea.endX =  FILE##PngResource.endX; \
    m_ValidDataArea.endY = FILE##PngResource.endY;

#define GET_PNG_RESOURCE(FILE) \
    FILE##PngResource.uClsinfo

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

#define FRONT_LEFT_INSIDE_ONE_STEP          "pdc_front_left_inside_1"
#define FRONT_LEFT_INSIDE_TWO_STEP          "pdc_front_left_inside_2"
#define FRONT_LEFT_INSIDE_THREE_STEP        "pdc_front_left_inside_3"
#define FRONT_LEFT_INSIDE_FOUR_STEP         "pdc_front_left_inside_4"
#define FRONT_LEFT_INSIDE_FIVE_STEP         "pdc_front_left_inside_5"
#define FRONT_LEFT_INSIDE_SIX_STEP          "pdc_front_left_inside_6"
#define FRONT_LEFT_INSIDE_SEVEN_STEP        "pdc_front_left_inside_7"
#define FRONT_LEFT_INSIDE_EIGHT_STEP        "pdc_front_left_inside_8"
#define FRONT_LEFT_INSIDE_NINE_STEP         "pdc_front_left_inside_9"

#define FRONT_LEFT_ONE_STEP                 "pdc_front_left_1"
#define FRONT_LEFT_TWO_STEP                 "pdc_front_left_2"
#define FRONT_LEFT_THREE_STEP               "pdc_front_left_3"
#define FRONT_LEFT_FOUR_STEP                "pdc_front_left_4"
#define FRONT_LEFT_FIVE_STEP                "pdc_front_left_5"
#define FRONT_LEFT_SIX_STEP                 "pdc_front_left_6"
#define FRONT_LEFT_SEVEN_STEP               "pdc_front_left_7"
#define FRONT_LEFT_EIGHT_STEP               "pdc_front_left_8"
#define FRONT_LEFT_NINE_STEP                "pdc_front_left_9"

#define FRONT_RIGHT_ONE_STEP                "pdc_front_right_1"
#define FRONT_RIGHT_TWO_STEP                "pdc_front_right_2"
#define FRONT_RIGHT_THREE_STEP              "pdc_front_right_3"
#define FRONT_RIGHT_FOUR_STEP               "pdc_front_right_4"
#define FRONT_RIGHT_FIVE_STEP               "pdc_front_right_5"
#define FRONT_RIGHT_SIX_STEP                "pdc_front_right_6"
#define FRONT_RIGHT_SEVEN_STEP              "pdc_front_right_7"
#define FRONT_RIGHT_EIGHT_STEP              "pdc_front_right_8"
#define FRONT_RIGHT_NINE_STEP               "pdc_front_right_9"

#define FRONT_RIGHT_INSIDE_ONE_STEP         "pdc_front_right_inside_1"
#define FRONT_RIGHT_INSIDE_TWO_STEP         "pdc_front_right_inside_2"
#define FRONT_RIGHT_INSIDE_THREE_STEP       "pdc_front_right_inside_3"
#define FRONT_RIGHT_INSIDE_FOUR_STEP        "pdc_front_right_inside_4"
#define FRONT_RIGHT_INSIDE_FIVE_STEP        "pdc_front_right_inside_5"
#define FRONT_RIGHT_INSIDE_SIX_STEP         "pdc_front_right_inside_6"
#define FRONT_RIGHT_INSIDE_SEVEN_STEP       "pdc_front_right_inside_7"
#define FRONT_RIGHT_INSIDE_EIGHT_STEP       "pdc_front_right_inside_8"
#define FRONT_RIGHT_INSIDE_NINE_STEP        "pdc_front_right_inside_9"

//----------------------------------------------------------------------------

#define REAR_LEFT_INSIDE_ONE_STEP           "pdc_rear_left_inside_1"
#define REAR_LEFT_INSIDE_TWO_STEP           "pdc_rear_left_inside_2"
#define REAR_LEFT_INSIDE_THREE_STEP         "pdc_rear_left_inside_3"
#define REAR_LEFT_INSIDE_FOUR_STEP          "pdc_rear_left_inside_4"
#define REAR_LEFT_INSIDE_FIVE_STEP          "pdc_rear_left_inside_5"
#define REAR_LEFT_INSIDE_SIX_STEP           "pdc_rear_left_inside_6"
#define REAR_LEFT_INSIDE_SEVEN_STEP         "pdc_rear_left_inside_7"
#define REAR_LEFT_INSIDE_EIGHT_STEP         "pdc_rear_left_inside_8"
#define REAR_LEFT_INSIDE_NINE_STEP          "pdc_rear_left_inside_9"

#define REAR_LEFT_ONE_STEP                  "pdc_rear_left_1"
#define REAR_LEFT_TWO_STEP                  "pdc_rear_left_2"
#define REAR_LEFT_THREE_STEP                "pdc_rear_left_3"
#define REAR_LEFT_FOUR_STEP                 "pdc_rear_left_4"
#define REAR_LEFT_FIVE_STEP                 "pdc_rear_left_5"
#define REAR_LEFT_SIX_STEP                  "pdc_rear_left_6"
#define REAR_LEFT_SEVEN_STEP                "pdc_rear_left_7"
#define REAR_LEFT_EIGHT_STEP                "pdc_rear_left_8"
#define REAR_LEFT_NINE_STEP                 "pdc_rear_left_9"

#define REAR_RIGHT_ONE_STEP                 "pdc_rear_right_1"
#define REAR_RIGHT_TWO_STEP                 "pdc_rear_right_2"
#define REAR_RIGHT_THREE_STEP               "pdc_rear_right_3"
#define REAR_RIGHT_FOUR_STEP                "pdc_rear_right_4"
#define REAR_RIGHT_FIVE_STEP                "pdc_rear_right_5"
#define REAR_RIGHT_SIX_STEP                 "pdc_rear_right_6"
#define REAR_RIGHT_SEVEN_STEP               "pdc_rear_right_7"
#define REAR_RIGHT_EIGHT_STEP               "pdc_rear_right_8"
#define REAR_RIGHT_NINE_STEP                "pdc_rear_right_9"

#define REAR_RIGHT_INSIDE_ONE_STEP          "pdc_rear_right_inside_1"
#define REAR_RIGHT_INSIDE_TWO_STEP          "pdc_rear_right_inside_2"
#define REAR_RIGHT_INSIDE_THREE_STEP        "pdc_rear_right_inside_3"
#define REAR_RIGHT_INSIDE_FOUR_STEP         "pdc_rear_right_inside_4"
#define REAR_RIGHT_INSIDE_FIVE_STEP         "pdc_rear_right_inside_5"
#define REAR_RIGHT_INSIDE_SIX_STEP          "pdc_rear_right_inside_6"
#define REAR_RIGHT_INSIDE_SEVEN_STEP        "pdc_rear_right_inside_7"
#define REAR_RIGHT_INSIDE_EIGHT_STEP        "pdc_rear_right_inside_8"
#define REAR_RIGHT_INSIDE_NINE_STEP         "pdc_rear_right_inside_9"

#define PDC_CAR                             "pdc_fiesta"

#define PDC_ROAD                            "pdc_road"

#define PDC_BACKGROUND                      "popup_default"

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_RESOURCEPNGDEFINE_H__