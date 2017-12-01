
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_COLORBLOCK_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_COLORBLOCK_H__

#include "ADASManager/PAS/GraphicCore/PasUtils.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class ColorBlock
{
public:
    ColorBlock(const string& pngResourceFile);

    virtual ~ColorBlock();

    virtual void CompoundArea();

    virtual void DeCompoundArea();

public:
    VALIDEREA m_ValidDataArea;

    UInt32 m_uiWidth = 0;
    UInt32 m_uiHight = 0;
    UInt32 m_uiLength = 0;

    const string& m_sPngResourceFile;

    BOOLEAN m_bIsDecoratored = FALSE;

    BYTE* m_HasCompoundedAreaHolder = nullptr;

    BYTE* m_pColorBlockBuffer = nullptr;

    //BOOLEAN m_bIsDecoratoredHistory = FALSE;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_COLORBLOCK_H__