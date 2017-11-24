
#include "ADASManager/PAS/RearLeftInside.h"
#include "ADASManager/PAS/DefaultArea.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

RearLeftInside::RearLeftInside(Area* area)
{
    m_vRearLeftInsideColorBlockArray.push_back(((DefaultArea*)area)->m_pRearLeftInsideDefault);
    m_vRearLeftInsideColorBlockArray.push_back(new RearLeftInsideOneStep(REAR_LEFT_INSIDE_ONE_STEP, TRUE, ((DefaultArea*)area)->m_pRearLeftInsideDefault));
    m_vRearLeftInsideColorBlockArray.push_back(new RearLeftInsideTwoStep(REAR_LEFT_INSIDE_TWO_STEP, TRUE, ((DefaultArea*)area)->m_pRearLeftInsideDefault));
    m_vRearLeftInsideColorBlockArray.push_back(new RearLeftInsideThreeStep(REAR_LEFT_INSIDE_THREE_STEP, TRUE, ((DefaultArea*)area)->m_pRearLeftInsideDefault));
}

RearLeftInside::~RearLeftInside()
{
    for(auto val : m_vRearLeftInsideColorBlockArray) {
        delete ((ColorBlock*)val);
    }
}

RearLeftInsideDefault::RearLeftInsideDefault(const string& pngResourceFile, const BOOLEAN isCalculateValidErea)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(nullptr)
{
}

void RearLeftInsideDefault::CompoundArea()
{
    for(UInt32 k = m_ValidDataArea.beginIndex; k <= m_ValidDataArea.endIndex;){
        if(m_pColorBlockBuffer[k+3] != 0)
        {
            m_pHasCompoundedArea[k] =  m_pColorBlockBuffer[k];
            m_pHasCompoundedArea[k+1] =  m_pColorBlockBuffer[k+1];
            m_pHasCompoundedArea[k+2] =  m_pColorBlockBuffer[k+2];
            m_pHasCompoundedArea[k+3] =  m_pColorBlockBuffer[k+3];
        }
        k = k+4;
    }
}

void RearLeftInsideDefault::DeCompoundArea()
{

}

RearLeftInsideOneStep::RearLeftInsideOneStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(area)
{

}

void RearLeftInsideOneStep::CompoundArea()
{
    m_pArea->CompoundArea();

    for(UInt32 k = m_ValidDataArea.beginIndex; k <= m_ValidDataArea.endIndex;){
        if(m_pColorBlockBuffer[k+3] != 0)
        {
            m_pHasCompoundedArea[k] =  m_pColorBlockBuffer[k];
            m_pHasCompoundedArea[k+1] =  m_pColorBlockBuffer[k+1];
            m_pHasCompoundedArea[k+2] =  m_pColorBlockBuffer[k+2];
            m_pHasCompoundedArea[k+3] =  m_pColorBlockBuffer[k+3];
        }
        k = k+4;
    }
}

void RearLeftInsideOneStep::DeCompoundArea()
{

}

RearLeftInsideTwoStep::RearLeftInsideTwoStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(area)
{

}

void RearLeftInsideTwoStep::CompoundArea()
{
    m_pArea->CompoundArea();

    for(UInt32 k = m_ValidDataArea.beginIndex; k <= m_ValidDataArea.endIndex;){
        if(m_pColorBlockBuffer[k+3] != 0)
        {
            m_pHasCompoundedArea[k] =  m_pColorBlockBuffer[k];
            m_pHasCompoundedArea[k+1] =  m_pColorBlockBuffer[k+1];
            m_pHasCompoundedArea[k+2] =  m_pColorBlockBuffer[k+2];
            m_pHasCompoundedArea[k+3] =  m_pColorBlockBuffer[k+3];
        }
        k = k+4;
    }
}

void RearLeftInsideTwoStep::DeCompoundArea()
{

}

RearLeftInsideThreeStep::RearLeftInsideThreeStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(area)
{

}

void RearLeftInsideThreeStep::CompoundArea()
{
    m_pArea->CompoundArea();

    for(UInt32 k = m_ValidDataArea.beginIndex; k <= m_ValidDataArea.endIndex;){
        if(m_pColorBlockBuffer[k+3] != 0)
        {
            m_pHasCompoundedArea[k] =  m_pColorBlockBuffer[k];
            m_pHasCompoundedArea[k+1] =  m_pColorBlockBuffer[k+1];
            m_pHasCompoundedArea[k+2] =  m_pColorBlockBuffer[k+2];
            m_pHasCompoundedArea[k+3] =  m_pColorBlockBuffer[k+3];
        }
        k = k+4;
    }
}

void RearLeftInsideThreeStep::DeCompoundArea()
{

}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman