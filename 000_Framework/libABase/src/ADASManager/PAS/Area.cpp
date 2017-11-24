
#include "ADASManager/PAS/Area.h"

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
        memset(buffer, 0, 152*228*4);
        return buffer;
    }
    return nullptr;
}

BYTE* Area::m_pHasCompoundedArea = MallocBuffer();

Area::Area()
{

}

DecoratorArea::DecoratorArea(Area* area)
    : m_pArea(area)
{
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman