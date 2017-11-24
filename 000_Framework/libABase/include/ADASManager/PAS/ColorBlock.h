
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
    ColorBlock(const string& pngResourceFile, const BOOLEAN isCalculateValidErea);

    virtual ~ColorBlock();

private:
    void FillColorBlockBuffer(const BOOLEAN isCalculateValidErea);

public:
    VALIDEREA m_ValidDataArea;

    UInt32 m_uiWidth = 0;
    UInt32 m_uiHight = 0;

    BYTE* m_pColorBlockBuffer = nullptr;

    const string& m_sPngResourceFile;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_COLORBLOCK_H__