
#include "ADASManager/PAS/Car.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

#include "./Res/pdc_fiesta.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

Car::Car(const string& pngResourceFile, BYTE* const carCompoundedBuffer)
    : ColorBlock(pngResourceFile, carCompoundedBuffer, GET_PNG_RESOURCE(pdc_fiesta))
{
    GET_PNG_ARGS(pdc_fiesta)
}

// VOID Car::SetHandler(const PASMessageHandler* const handler) const
// {
//     m_pHandler = handler;
// }

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman