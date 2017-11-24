
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_PASMANAGER_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_PASMANAGER_H__

#include "ADASManager/PAS/FrontLeftInside.h"
#include "ADASManager/PAS/FrontLeft.h"
#include "ADASManager/PAS/FrontRight.h"
#include "ADASManager/PAS/FrontRightInside.h"

#include "ADASManager/PAS/RearLeftInside.h"
#include "ADASManager/PAS/RearLeft.h"
#include "ADASManager/PAS/RearRight.h"
#include "ADASManager/PAS/RearRightInside.h"

#include "ADASManager/PAS/DefaultArea.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class PasManager
{
public:
    static PasManager* GetInstance();

    static void DelInstance();

    PasManager(const PasManager&) = delete;
    PasManager& operator=(const PasManager&) = delete;

    ~PasManager();

private:
    PasManager();

public:
    FrontLeftInside* m_pFrontLeftInside = nullptr;
    FrontLeft* m_pFrontLeft = nullptr;
    FrontRight* m_pFrontRight = nullptr;
    FrontRightInside* m_pFrontRightInside = nullptr;

    RearLeftInside* m_pRearLeftInside = nullptr;
    RearLeft* m_pRearLeft = nullptr;
    RearRight* m_pRearRight = nullptr;
    RearRightInside* m_pRearRightInside = nullptr;

    DefaultArea* m_pDefaultArea = nullptr;

    static PasManager* m_pInstance;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_PASMANAGER_H__