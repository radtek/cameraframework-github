
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_DEFAULTAREA_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_DEFAULTAREA_H__

#include "ADASManager/PAS/Area.h"

#include "ADASManager/PAS/FrontLeftInside.h"
#include "ADASManager/PAS/FrontLeft.h"
#include "ADASManager/PAS/FrontRight.h"
#include "ADASManager/PAS/FrontRightInside.h"

#include "ADASManager/PAS/RearLeftInside.h"
#include "ADASManager/PAS/RearLeft.h"
#include "ADASManager/PAS/RearRight.h"
#include "ADASManager/PAS/RearRightInside.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class DefaultArea : public Area
{
public:
    DefaultArea();

    ~DefaultArea()
    {
        // if(nullptr != m_pFrontLeftInsideDefault){
        //     delete m_pFrontLeftInsideDefault;
        //     m_pFrontLeftInsideDefault = nullptr;
        // }

        // if(nullptr != m_pFrontLeftDefault){
        //     delete m_pFrontLeftDefault;
        //     m_pFrontLeftDefault = nullptr;
        // }

        // if(nullptr != m_pFrontRightDefault){
        //     delete m_pFrontRightDefault;
        //     m_pFrontRightDefault = nullptr;
        // }

        // if(nullptr != m_pFrontRightInsideDefault){
        //     delete m_pFrontRightInsideDefault;
        //     m_pFrontRightInsideDefault = nullptr;
        // }

        // if(nullptr != m_pRearLeftInsideDefault){
        //     delete m_pRearLeftInsideDefault;
        //     m_pRearLeftInsideDefault = nullptr;
        // }

        // if(nullptr != m_pRearLeftDefault){
        //     delete m_pRearLeftDefault;
        //     m_pRearLeftDefault = nullptr;
        // }

        // if(nullptr != m_pRearRightDefault){
        //     delete m_pRearRightDefault;
        //     m_pRearRightDefault = nullptr;
        // }

        // if(nullptr != m_pRearRightInsideDefault){
        //     delete m_pRearRightInsideDefault;
        //     m_pRearRightInsideDefault = nullptr;
        // }
    }

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;

public:
    FrontLeftInsideDefault* m_pFrontLeftInsideDefault = nullptr;
    FrontLeftDefault* m_pFrontLeftDefault = nullptr;
    FrontRightDefault* m_pFrontRightDefault = nullptr;
    FrontRightInsideDefault* m_pFrontRightInsideDefault = nullptr;

    RearLeftInsideDefault* m_pRearLeftInsideDefault = nullptr;
    RearLeftDefault* m_pRearLeftDefault = nullptr;
    RearRightDefault* m_pRearRightDefault = nullptr;
    RearRightInsideDefault* m_pRearRightInsideDefault = nullptr;

    std::vector<Area*> m_vColorBlockDefaultArray;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_DEFAULTAREA_H__