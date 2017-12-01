
#include "ADASManager/PAS/ColorBlock.h"
#include "ADASManager/PAS/GraphicCore/PasUtils.h"
#include "ADASManager/PAS/PasManager.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

ColorBlock::ColorBlock(const string& pngResourceFile)
    : m_sPngResourceFile(pngResourceFile)
{
}

ColorBlock::~ColorBlock()
{
}

void ColorBlock::CompoundArea()
{
    UInt32 compoundedAreaIndex = m_ValidDataArea.beginIndex;
    UInt32 clsinfoIndex = 0;
    while(compoundedAreaIndex <= m_ValidDataArea.endIndex){
        if(m_pColorBlockBuffer[clsinfoIndex+3] != 0){
            m_HasCompoundedAreaHolder[compoundedAreaIndex] =  m_pColorBlockBuffer[clsinfoIndex];
            m_HasCompoundedAreaHolder[compoundedAreaIndex+1] =  m_pColorBlockBuffer[clsinfoIndex+1];
            m_HasCompoundedAreaHolder[compoundedAreaIndex+2] =  m_pColorBlockBuffer[clsinfoIndex+2];
            m_HasCompoundedAreaHolder[compoundedAreaIndex+3] =  m_pColorBlockBuffer[clsinfoIndex+3];
        }

        compoundedAreaIndex += 4;
        clsinfoIndex += 4;
    }

    m_bIsDecoratored = TRUE;
    //m_bIsDecoratoredHistory = TRUE;
}

void ColorBlock::DeCompoundArea()
{
    UInt32 compoundedAreaIndex = m_ValidDataArea.beginIndex;
    UInt32 clsinfoIndex = 0;
    while(compoundedAreaIndex <= m_ValidDataArea.endIndex){
        if(m_pColorBlockBuffer[clsinfoIndex+3] != 0){
            m_HasCompoundedAreaHolder[compoundedAreaIndex] =  0;
            m_HasCompoundedAreaHolder[compoundedAreaIndex+1] =  0;
            m_HasCompoundedAreaHolder[compoundedAreaIndex+2] =  0;
            m_HasCompoundedAreaHolder[compoundedAreaIndex+3] =  0;
        }

        compoundedAreaIndex += 4;
        clsinfoIndex += 4;
    }

    m_bIsDecoratored = FALSE;
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman