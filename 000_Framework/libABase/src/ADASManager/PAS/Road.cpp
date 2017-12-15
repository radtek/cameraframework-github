
#include "ADASManager/PAS/Road.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

#include "./Res/pdc_road.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

Road::Road(const string& pngResourceFile, BYTE* const backgroundBuffer)
    : ColorBlock(pngResourceFile, backgroundBuffer, GET_PNG_RESOURCE(pdc_road))
{
    GET_PNG_ARGS(pdc_road)
}

// VOID Road::SetHandler(const PASMessageHandler* const handler) const
// {
//     m_pHandler = handler;
// }

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman