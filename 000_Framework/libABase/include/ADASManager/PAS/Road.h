
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_ROAD_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_ROAD_H__

#include "ADASManager/PAS/ColorBlock.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

//class PASMessageHandler;

class Road : public ColorBlock
{
public:
    Road(const string& pngResourceFile, BYTE* const backgroundBuffer);

    //VOID SetHandler(const PASMessageHandler* const handler) const;

public:
    //const PASMessageHandler* m_pHandler = nullptr;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_ROAD_H__