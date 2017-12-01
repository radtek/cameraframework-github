
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_RADARSENSER_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_RADARSENSER_H__

#include "ADASManager/PAS/ColorBlock.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class RadarSenser
{
public:
    RadarSenser(const string& radarSenserName);

    virtual ~RadarSenser();

    void Flush(UInt32 degree);

public:
    vector<ColorBlock*> m_vColorBlockArray;

    const string& m_strRadarSenserName;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_RADARSENSER_H__