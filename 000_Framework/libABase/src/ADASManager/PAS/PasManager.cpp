
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

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

static BYTE* MallocBuffer()
{
    unsigned char* buffer = (unsigned char*)malloc(152*228*4);
    if(nullptr != buffer)
    {
        memset(buffer, '\x00', 152*228*4);
        return buffer;
    }

    ASSERT(buffer != NULL);

    return nullptr;
}

BYTE* PasManager::m_pHasCompoundedArea = MallocBuffer();

static BYTE* MallocBufferBackGround()
{
    unsigned char* buffer = (unsigned char*)malloc(640*720*4);

    if(NULL != buffer)
    {
        memset(buffer, 0, 640*720*4);

        for(int i = 0; i < 640*720*4;){
            buffer[i+3] = 255;
            i += 4;
        }

        return buffer;
    }

    ASSERT(buffer != NULL);

    return nullptr;
}

BYTE* PasManager::m_pHasCompoundedBackGround = MallocBufferBackGround();

static BYTE* MallocBufferCar()
{
    unsigned char* buffer = (unsigned char*)malloc(152*228*4);
    if(nullptr != buffer)
    {
        memset(buffer, '\x00', 152*228*4);
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
    if (m_pInstance != nullptr)
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
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
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman