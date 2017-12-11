
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAR_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAR_H__

#include "ADASManager/PAS/ColorBlock.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

//class PASMessageHandler;

class Car : public ColorBlock
{
public:
    Car(const string& pngResourceFile, BYTE* const carCompoundedBuffer);

    //VOID SetHandler(const PASMessageHandler* const handler) const;

public:
    //const PASMessageHandler* m_pHandler = nullptr;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAR_H__