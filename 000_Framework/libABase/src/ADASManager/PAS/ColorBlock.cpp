
#include "ADASManager/PAS/ColorBlock.h"
#include "ADASManager/PAS/GraphicCore/PasUtils.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

ColorBlock::ColorBlock(const string& pngResourceFile, const BOOLEAN isCalculateValidArea)
    : m_sPngResourceFile(pngResourceFile)
{
    ALOGD(" ColorBlock::ColorBlock : m_sPngResourceFile = %s\n", m_sPngResourceFile.c_str());

    FillColorBlockBuffer(isCalculateValidArea);
}

ColorBlock::~ColorBlock()
{
    if(nullptr != m_pColorBlockBuffer){
        free(m_pColorBlockBuffer);
        m_pColorBlockBuffer = nullptr;
    }
}

void ColorBlock::FillColorBlockBuffer(const BOOLEAN isCalculateValidArea)
{
    if(isCalculateValidArea) {
        m_pColorBlockBuffer = PasUtils::LodePNGImage(m_sPngResourceFile, &m_uiWidth, &m_uiHight, isCalculateValidArea, &m_ValidDataArea);
    }else{
        m_pColorBlockBuffer = PasUtils::LodePNGImage(m_sPngResourceFile, &m_uiWidth, &m_uiHight, isCalculateValidArea, nullptr);
    }
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman