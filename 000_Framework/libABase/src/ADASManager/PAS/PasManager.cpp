
#include "ADASManager/PAS/PasManager.h"

#include "ADASManager/PAS/FrontLeftInside.h"
#include "ADASManager/PAS/FrontLeft.h"
#include "ADASManager/PAS/FrontRight.h"
#include "ADASManager/PAS/FrontRightInside.h"

#include "ADASManager/PAS/RearLeftInside.h"
#include "ADASManager/PAS/RearLeft.h"
#include "ADASManager/PAS/RearRight.h"
#include "ADASManager/PAS/RearRightInside.h"

#include "ADASManager/PAS/Car.h"
#include "ADASManager/PAS/Road.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

static BYTE* MallocBufferColorBlock()
{
    unsigned char* buffer = (unsigned char*)malloc(PAS_SCREEN_WIDTH * PAS_SCREEN_HIGHT * 4);
    if(nullptr != buffer) {
        memset(buffer, 0, PAS_SCREEN_WIDTH * PAS_SCREEN_HIGHT * 4);
        return buffer;
    }

    ASSERT(buffer != NULL);

    return nullptr;
}

BYTE* PasManager::m_pHasCompoundedArea = MallocBufferColorBlock();

static BYTE* MallocBufferBackGround()
{
    unsigned char* buffer = (unsigned char*)malloc(PAS_SCREEN_WIDTH * PAS_SCREEN_HIGHT * 4);

    if(NULL != buffer) {
        memset(buffer, 0, PAS_SCREEN_WIDTH * PAS_SCREEN_HIGHT * 4);

        for(int i = 0; i < PAS_SCREEN_WIDTH * PAS_SCREEN_HIGHT * 4;){
            buffer[i+3] = 255;
            i += 4;
        }

        return buffer;
    }

    ASSERT(buffer != NULL);

    return nullptr;
}

BYTE* PasManager::m_pHasCompoundedBackGround = MallocBufferBackGround();
BYTE* PasManager::m_pRoadBuffer = m_pHasCompoundedBackGround;

static BYTE* MallocBufferCar()
{
    unsigned char* buffer = (unsigned char*)malloc(PAS_SCREEN_WIDTH * PAS_SCREEN_HIGHT * 4);
    if(nullptr != buffer) {
        memset(buffer, 0, PAS_SCREEN_WIDTH * PAS_SCREEN_HIGHT * 4);
        return buffer;
    }

    ASSERT(buffer != NULL);

    return nullptr;
}

BYTE* PasManager::m_pCarBuffer = MallocBufferCar();

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
    if (m_pInstance != nullptr){
        delete m_pInstance;
        m_pInstance = nullptr;
    }
}

VOID PasManager::SetHandler(PASMessageHandler* handler) const
{
    m_pFrontLeftInside->SetHandler(handler);
    m_pFrontLeft->SetHandler(handler);
    m_pFrontRight->SetHandler(handler);
    m_pFrontRightInside->SetHandler(handler);

    m_pRearLeftInside->SetHandler(handler);
    m_pRearLeft->SetHandler(handler);
    m_pRearRight->SetHandler(handler);
    m_pRearRightInside->SetHandler(handler);

    //m_pCar->SetHandler(handler);
}

PasManager::PasManager()
{
    m_pFrontLeftInside = new FrontLeftInside("FrontLeftInside", m_pHasCompoundedArea);
    m_pFrontLeft = new FrontLeft("FrontLeft", m_pHasCompoundedArea);
    m_pFrontRight = new FrontRight("FrontRight", m_pHasCompoundedArea);
    m_pFrontRightInside = new FrontRightInside("FrontRightInside", m_pHasCompoundedArea);

    m_pRearLeftInside = new RearLeftInside("RearLeftInside", m_pHasCompoundedArea);
    m_pRearLeft = new RearLeft("RearLeft", m_pHasCompoundedArea);
    m_pRearRight = new RearRight("RearRight", m_pHasCompoundedArea);
    m_pRearRightInside = new RearRightInside("RearRightInside", m_pHasCompoundedArea);

    m_pCar = new Car("Car", m_pCarBuffer);
    m_pCar->CompoundArea();

    m_pRoad = new Road("Road", m_pRoadBuffer);
    m_pRoad->CompoundArea();
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

    if(nullptr != m_pCar){
        delete m_pCar;
        m_pCar = nullptr;
    }

    if(nullptr != m_pRoad){
        delete m_pRoad;
        m_pRoad = nullptr;
    }

    if(nullptr != m_pHasCompoundedArea){
        free(m_pHasCompoundedArea);
        m_pHasCompoundedArea = nullptr;
    }

    if(nullptr != m_pHasCompoundedBackGround){
        free(m_pHasCompoundedBackGround);
        m_pHasCompoundedBackGround = nullptr;
    }

    if(nullptr != m_pCarBuffer){
        free(m_pCarBuffer);
        m_pCarBuffer = nullptr;
    }
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman