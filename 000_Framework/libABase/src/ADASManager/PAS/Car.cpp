
#include "ADASManager/PAS/Car.h"


#include "./Res/pdc_fiesta.h"

#include "./Res/pdc_front_left_0.h"
#include "./Res/pdc_front_left_inside_0.h"
#include "./Res/pdc_front_right_0.h"
#include "./Res/pdc_front_right_inside_0.h"

#include "./Res/pdc_rear_left_0.h"
#include "./Res/pdc_rear_left_inside_0.h"
#include "./Res/pdc_rear_right_0.h"
#include "./Res/pdc_rear_right_inside_0.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

Car::Car(const string& pngResourceFile, BYTE* carBuffer)
    : ColorBlock(pngResourceFile)
{
    m_uiLength = pdc_fiestaPngResource.length;
    m_uiWidth = pdc_fiestaPngResource.width;
    m_uiHight = pdc_fiestaPngResource.hight;
    m_ValidDataArea.beginIndex =  pdc_fiestaPngResource.beginIndex;
    m_ValidDataArea.endIndex = pdc_fiestaPngResource.endIndex;
    m_pColorBlockBuffer = const_cast<BYTE*>(pdc_fiestaPngResource.uClsinfo);

    m_HasCompoundedAreaHolder = carBuffer;
}

void Car::CompoundArea()
{
//     UInt32 compoundedAreaIndex = 0;
//     UInt32 clsinfoIndex = 0;


// //-----------------------pdc_front_left_0PngResource------------------------------------------
//     compoundedAreaIndex = pdc_front_left_0PngResource.beginIndex;
//     while(compoundedAreaIndex <= pdc_front_left_0PngResource.endIndex){
//         if(pdc_front_left_0PngResource.uClsinfo[clsinfoIndex+3] != 0){
//             m_HasCompoundedAreaHolder[compoundedAreaIndex] =  pdc_front_left_0PngResource.uClsinfo[clsinfoIndex];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+1] =  pdc_front_left_0PngResource.uClsinfo[clsinfoIndex+1];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+2] =  pdc_front_left_0PngResource.uClsinfo[clsinfoIndex+2];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+3] =  pdc_front_left_0PngResource.uClsinfo[clsinfoIndex+3];
//         }

//         compoundedAreaIndex += 4;
//         clsinfoIndex += 4;
//     }
// //-----------------------pdc_front_left_inside_0PngResource------------------------------------------
//     compoundedAreaIndex = pdc_front_left_inside_0PngResource.beginIndex;
//     clsinfoIndex = 0;
//     while(compoundedAreaIndex <= pdc_front_left_inside_0PngResource.endIndex){
//         if(pdc_front_left_inside_0PngResource.uClsinfo[clsinfoIndex+3] != 0){
//             m_HasCompoundedAreaHolder[compoundedAreaIndex] =  pdc_front_left_inside_0PngResource.uClsinfo[clsinfoIndex];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+1] =  pdc_front_left_inside_0PngResource.uClsinfo[clsinfoIndex+1];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+2] =  pdc_front_left_inside_0PngResource.uClsinfo[clsinfoIndex+2];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+3] =  pdc_front_left_inside_0PngResource.uClsinfo[clsinfoIndex+3];
//         }

//         compoundedAreaIndex += 4;
//         clsinfoIndex += 4;
//     }

// //-----------------------pdc_front_right_0PngResource------------------------------------------
//     compoundedAreaIndex = pdc_front_right_0PngResource.beginIndex;
//     clsinfoIndex = 0;
//     while(compoundedAreaIndex <= pdc_front_right_0PngResource.endIndex){
//         if(pdc_front_right_0PngResource.uClsinfo[clsinfoIndex+3] != 0){
//             m_HasCompoundedAreaHolder[compoundedAreaIndex] =  pdc_front_right_0PngResource.uClsinfo[clsinfoIndex];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+1] =  pdc_front_right_0PngResource.uClsinfo[clsinfoIndex+1];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+2] =  pdc_front_right_0PngResource.uClsinfo[clsinfoIndex+2];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+3] =  pdc_front_right_0PngResource.uClsinfo[clsinfoIndex+3];
//         }

//         compoundedAreaIndex += 4;
//         clsinfoIndex += 4;
//     }


// //-----------------------pdc_front_right_inside_0PngResource------------------------------------------
//     compoundedAreaIndex = pdc_front_right_inside_0PngResource.beginIndex;
//     clsinfoIndex = 0;
//     while(compoundedAreaIndex <= pdc_front_right_inside_0PngResource.endIndex){
//         if(pdc_front_right_inside_0PngResource.uClsinfo[clsinfoIndex+3] != 0){
//             m_HasCompoundedAreaHolder[compoundedAreaIndex] =  pdc_front_right_inside_0PngResource.uClsinfo[clsinfoIndex];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+1] =  pdc_front_right_inside_0PngResource.uClsinfo[clsinfoIndex+1];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+2] =  pdc_front_right_inside_0PngResource.uClsinfo[clsinfoIndex+2];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+3] =  pdc_front_right_inside_0PngResource.uClsinfo[clsinfoIndex+3];
//         }

//         compoundedAreaIndex += 4;
//         clsinfoIndex += 4;
//     }

// //-----------------------pdc_rear_left_0PngResource------------------------------------------
//     compoundedAreaIndex = pdc_rear_left_0PngResource.beginIndex;
//     clsinfoIndex = 0;
//     while(compoundedAreaIndex <= pdc_rear_left_0PngResource.endIndex){
//         if(pdc_rear_left_0PngResource.uClsinfo[clsinfoIndex+3] != 0){
//             m_HasCompoundedAreaHolder[compoundedAreaIndex] =  pdc_rear_left_0PngResource.uClsinfo[clsinfoIndex];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+1] =  pdc_rear_left_0PngResource.uClsinfo[clsinfoIndex+1];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+2] =  pdc_rear_left_0PngResource.uClsinfo[clsinfoIndex+2];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+3] =  pdc_rear_left_0PngResource.uClsinfo[clsinfoIndex+3];
//         }

//         compoundedAreaIndex += 4;
//         clsinfoIndex += 4;
//     }

// //-----------------------pdc_rear_left_inside_0PngResource------------------------------------------
//     compoundedAreaIndex = pdc_rear_left_inside_0PngResource.beginIndex;
//     clsinfoIndex = 0;
//     while(compoundedAreaIndex <= pdc_rear_left_inside_0PngResource.endIndex){
//         if(pdc_rear_left_inside_0PngResource.uClsinfo[clsinfoIndex+3] != 0){
//             m_HasCompoundedAreaHolder[compoundedAreaIndex] =  pdc_rear_left_inside_0PngResource.uClsinfo[clsinfoIndex];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+1] =  pdc_rear_left_inside_0PngResource.uClsinfo[clsinfoIndex+1];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+2] =  pdc_rear_left_inside_0PngResource.uClsinfo[clsinfoIndex+2];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+3] =  pdc_rear_left_inside_0PngResource.uClsinfo[clsinfoIndex+3];
//         }

//         compoundedAreaIndex += 4;
//         clsinfoIndex += 4;
//     }

// //-----------------------pdc_rear_right_0PngResource------------------------------------------
//     compoundedAreaIndex = pdc_rear_right_0PngResource.beginIndex;
//     clsinfoIndex = 0;
//     while(compoundedAreaIndex <= pdc_rear_right_0PngResource.endIndex){
//         if(pdc_rear_right_0PngResource.uClsinfo[clsinfoIndex+3] != 0){
//             m_HasCompoundedAreaHolder[compoundedAreaIndex] =  pdc_rear_right_0PngResource.uClsinfo[clsinfoIndex];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+1] =  pdc_rear_right_0PngResource.uClsinfo[clsinfoIndex+1];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+2] =  pdc_rear_right_0PngResource.uClsinfo[clsinfoIndex+2];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+3] =  pdc_rear_right_0PngResource.uClsinfo[clsinfoIndex+3];
//         }

//         compoundedAreaIndex += 4;
//         clsinfoIndex += 4;
//     }

// //-----------------------pdc_rear_right_inside_0PngResource------------------------------------------
//     compoundedAreaIndex = pdc_rear_right_inside_0PngResource.beginIndex;
//     clsinfoIndex = 0;
//     while(compoundedAreaIndex <= pdc_rear_right_inside_0PngResource.endIndex){
//         if(pdc_rear_right_inside_0PngResource.uClsinfo[clsinfoIndex+3] != 0){
//             m_HasCompoundedAreaHolder[compoundedAreaIndex] =  pdc_rear_right_inside_0PngResource.uClsinfo[clsinfoIndex];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+1] =  pdc_rear_right_inside_0PngResource.uClsinfo[clsinfoIndex+1];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+2] =  pdc_rear_right_inside_0PngResource.uClsinfo[clsinfoIndex+2];
//             m_HasCompoundedAreaHolder[compoundedAreaIndex+3] =  pdc_rear_right_inside_0PngResource.uClsinfo[clsinfoIndex+3];
//         }

//         compoundedAreaIndex += 4;
//         clsinfoIndex += 4;
//     }

    //-----------------------car------------------------------------------
    ColorBlock::CompoundArea();
}

void Car::DeCompoundArea()
{
    //do not need a DeCompoundArea
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman