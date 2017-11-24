
#include "ADASManager/PAS/DefaultArea.h"
#include "ADASManager/PAS/ResourcePngDefine.h"
#include "ADASManager/PAS/Area.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

DefaultArea::DefaultArea()
{
    m_pFrontLeftInsideDefault = new FrontLeftInsideDefault(FRONT_LEFT_INSIDE_DEFAULT, TRUE);
    m_vColorBlockDefaultArray.push_back(m_pFrontLeftInsideDefault);
    m_pFrontLeftDefault = new FrontLeftDefault(FRONT_LEFT_DEFAULT, TRUE);
    m_vColorBlockDefaultArray.push_back(m_pFrontLeftDefault);
    m_pFrontRightDefault = new FrontRightDefault(FRONT_RIGHT_DEFAULT, TRUE);
    m_vColorBlockDefaultArray.push_back(m_pFrontRightDefault);
    m_pFrontRightInsideDefault = new FrontRightInsideDefault(FRONT_RIGHT_INSIDE_DEFAULT, TRUE);
    m_vColorBlockDefaultArray.push_back(m_pFrontRightInsideDefault);

    m_pRearLeftInsideDefault = new RearLeftInsideDefault(REAR_LEFT_INSIDE_DEFAULT, TRUE);
    m_vColorBlockDefaultArray.push_back(m_pRearLeftInsideDefault);
    m_pRearLeftDefault = new RearLeftDefault(REAR_LEFT_DEFAULT, TRUE);
    m_vColorBlockDefaultArray.push_back(m_pRearLeftDefault);
    m_pRearRightDefault = new RearRightDefault(REAR_RIGHT_DEFAULT, TRUE);
    m_vColorBlockDefaultArray.push_back(m_pRearRightDefault);
    m_pRearRightInsideDefault = new RearRightInsideDefault(REAR_RIGHT_INSIDE_DEFAULT, TRUE);
    m_vColorBlockDefaultArray.push_back(m_pRearRightInsideDefault);
}

void DefaultArea::CompoundArea()
{
    for(auto val : m_vColorBlockDefaultArray) {
        // UInt32 k = 0;
        // while(k < ((ColorBlock*)val)->m_uiWidth * ((ColorBlock*)val)->m_uiHight * 4)
        // {
        //     if(((ColorBlock*)val)->m_pColorBlockBuffer[k+3] != 0)
        //     {
        //         m_pHasCompoundedArea[k] =  ((ColorBlock*)val)->m_pColorBlockBuffer[k];
        //         m_pHasCompoundedArea[k+1] =  ((ColorBlock*)val)->m_pColorBlockBuffer[k+1];
        //         m_pHasCompoundedArea[k+2] =  ((ColorBlock*)val)->m_pColorBlockBuffer[k+2];
        //         m_pHasCompoundedArea[k+3] =  ((ColorBlock*)val)->m_pColorBlockBuffer[k+3];
        //     }
        //     k = k+4;
        // }
        ALOGD(" [%s, %d] DefaultArea::CompoundArea() val=%p\n", __FUNCTION__, __LINE__, val);
        val->CompoundArea();
        ALOGD(" [%s, %d] DefaultArea::CompoundArea() \n", __FUNCTION__, __LINE__);
    }
}

void DefaultArea::DeCompoundArea()
{

}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman