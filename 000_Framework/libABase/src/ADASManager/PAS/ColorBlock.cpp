
#include "ADASManager/PAS/ColorBlock.h"
#include "ADASManager/PAS/GraphicCore/PasUtils.h"
#include "ADASManager/PAS/PasManager.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

ColorBlock::ColorBlock(const string& pngResourceFile, BYTE* const compoundedBuffer, const BYTE* const srcBuffer)
    : m_sPngResourceFile(pngResourceFile)
    , m_HasCompoundedAreaHolder(compoundedBuffer)
    , m_pColorBlockBuffer(srcBuffer)
{
}

ColorBlock::~ColorBlock()
{
}

VOID ColorBlock::CompoundArea()
{
    UInt32 index = 0;
    for(UInt32 hightIndex = m_ValidDataArea.beginY; hightIndex <= m_ValidDataArea.endY; hightIndex++){  // hang
        for(UInt32 widthIndex = m_ValidDataArea.beginX; widthIndex <= m_ValidDataArea.endX; widthIndex++){ //lie
            if(m_pColorBlockBuffer[index+3] != 0) {
                m_HasCompoundedAreaHolder[4*hightIndex*m_uiWidth+4*widthIndex] =   m_pColorBlockBuffer[index];
                m_HasCompoundedAreaHolder[4*hightIndex*m_uiWidth+4*widthIndex+1] = m_pColorBlockBuffer[index + 1];
                m_HasCompoundedAreaHolder[4*hightIndex*m_uiWidth+4*widthIndex+2] = m_pColorBlockBuffer[index + 2];
                m_HasCompoundedAreaHolder[4*hightIndex*m_uiWidth+4*widthIndex+3] = m_pColorBlockBuffer[index + 3];
            }

            index += 4;
        }
    }

    m_bIsDecoratored = TRUE;
}

VOID ColorBlock::DeCompoundArea()
{
    UInt32 index = 0;
    for(UInt32 hightIndex = m_ValidDataArea.beginY; hightIndex <= m_ValidDataArea.endY; hightIndex++){  // hang
        for(UInt32 widthIndex = m_ValidDataArea.beginX; widthIndex <= m_ValidDataArea.endX; widthIndex++){ //lie
            if(m_pColorBlockBuffer[index+3] != 0) {
                m_HasCompoundedAreaHolder[4*hightIndex*m_uiWidth+4*widthIndex] =   0;
                m_HasCompoundedAreaHolder[4*hightIndex*m_uiWidth+4*widthIndex+1] = 0;
                m_HasCompoundedAreaHolder[4*hightIndex*m_uiWidth+4*widthIndex+2] = 0;
                m_HasCompoundedAreaHolder[4*hightIndex*m_uiWidth+4*widthIndex+3] = 0;
            }

            index += 4;
        }
    }

    m_bIsDecoratored = FALSE;
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman