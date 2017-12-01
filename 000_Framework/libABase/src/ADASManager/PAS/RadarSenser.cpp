
#include "ADASManager/PAS/RadarSenser.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

RadarSenser::RadarSenser(const string& radarSenserName)
    : m_strRadarSenserName(radarSenserName)
{
}

RadarSenser::~RadarSenser()
{
}

void RadarSenser::Flush(UInt32 degree)
{
    for(UInt32 i = m_vColorBlockArray.size()-1; i > 0; i--){
        if(i >= degree && m_vColorBlockArray[i]->m_bIsDecoratored == FALSE) {
            (m_vColorBlockArray[i])->CompoundArea();
        }

        if(i < degree && m_vColorBlockArray[i]->m_bIsDecoratored == TRUE) {
            (m_vColorBlockArray[i])->DeCompoundArea();
        }
    }
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman