
#include "ADASManager/PAS/PasManager.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

PasManager* PasManager::m_pInstance = nullptr;

PasManager* PasManager::GetInstance()
{
    if (m_pInstance == nullptr){
        m_pInstance = new PasManager();
    }
    return m_pInstance;
}

void PasManager::DelInstance()
{
    if (m_pInstance != nullptr)
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
}

PasManager::PasManager()
{
    ALOGD(" [%s, %d] PasManager::PasManager() \n", __FUNCTION__, __LINE__);

    m_pDefaultArea = new DefaultArea();

    m_pFrontLeftInside = new FrontLeftInside(m_pDefaultArea);
    m_pFrontLeft = new FrontLeft(m_pDefaultArea);
    m_pFrontRight = new FrontRight(m_pDefaultArea);
    m_pFrontRightInside = new FrontRightInside(m_pDefaultArea);

    m_pRearLeftInside = new RearLeftInside(m_pDefaultArea);
    m_pRearLeft = new RearLeft(m_pDefaultArea);
    m_pRearRight = new RearRight(m_pDefaultArea);
    m_pRearRightInside = new RearRightInside(m_pDefaultArea);

    ALOGD(" [%s, %d] PasManager::PasManager() \n", __FUNCTION__, __LINE__);

    m_pDefaultArea->CompoundArea();
}

PasManager::~PasManager()
{
    if(nullptr != m_pFrontLeftInside){
        delete m_pFrontLeftInside;
        m_pFrontLeftInside = nullptr;
    }

    if(nullptr != m_pFrontLeft){
        delete m_pFrontLeft;
        m_pFrontLeft = nullptr;
    }

    if(nullptr != m_pFrontRight){
        delete m_pFrontRight;
        m_pFrontRight = nullptr;
    }

    if(nullptr != m_pFrontRightInside){
        delete m_pFrontRightInside;
        m_pFrontRightInside = nullptr;
    }

    if(nullptr != m_pRearLeftInside){
        delete m_pRearLeftInside;
        m_pRearLeftInside = nullptr;
    }

    if(nullptr != m_pRearLeft){
        delete m_pRearLeft;
        m_pRearLeft = nullptr;
    }

    if(nullptr != m_pRearRight){
        delete m_pRearRight;
        m_pRearRight = nullptr;
    }

    if(nullptr != m_pRearRightInside){
        delete m_pRearRightInside;
        m_pRearRightInside = nullptr;
    }

    if(nullptr != m_pDefaultArea){
        delete m_pDefaultArea;
        m_pDefaultArea = nullptr;
    }
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman