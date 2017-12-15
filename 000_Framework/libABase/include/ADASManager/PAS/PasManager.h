
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_PASMANAGER_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_PASMANAGER_H__

#include "ADASManager/PAS/RadarSenser.h"
#include "ADASManager/PAS/ColorBlock.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class PASMessageHandler;

class PasManager
{
public:
    static PasManager* GetInstance();

    static void DelInstance();

    PasManager(const PasManager&) = delete;
    PasManager& operator=(const PasManager&) = delete;

    ~PasManager();

    VOID SetHandler(PASMessageHandler* handler) const;

private:
    PasManager();

public:
    RadarSenser* m_pFrontLeftInside = nullptr;
    RadarSenser* m_pFrontLeft = nullptr;
    RadarSenser* m_pFrontRight = nullptr;
    RadarSenser* m_pFrontRightInside = nullptr;

    RadarSenser* m_pRearLeftInside = nullptr;
    RadarSenser* m_pRearLeft = nullptr;
    RadarSenser* m_pRearRight = nullptr;
    RadarSenser* m_pRearRightInside = nullptr;

    ColorBlock* m_pCar = nullptr;
    ColorBlock* m_pRoad = nullptr;

    static PasManager* m_pInstance;

    static BYTE* m_pHasCompoundedArea;

    static BYTE* m_pHasCompoundedBackGround;

    static BYTE* m_pCarBuffer;

    static BYTE* m_pRoadBuffer;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_PASMANAGER_H__