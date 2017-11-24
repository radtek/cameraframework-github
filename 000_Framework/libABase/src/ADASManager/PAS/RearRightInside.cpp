
#include "ADASManager/PAS/RearRightInside.h"
#include "ADASManager/PAS/DefaultArea.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

RearRightInside::RearRightInside(Area* area)
{
    m_vRearRightInsideColorBlockArray.push_back(((DefaultArea*)area)->m_pRearRightInsideDefault);
    m_vRearRightInsideColorBlockArray.push_back(new RearRightInsideOneStep(REAR_RIGHT_INSIDE_ONE_STEP, TRUE, ((DefaultArea*)area)->m_pRearRightInsideDefault));
    m_vRearRightInsideColorBlockArray.push_back(new RearRightInsideTwoStep(REAR_RIGHT_INSIDE_TWO_STEP, TRUE, ((DefaultArea*)area)->m_pRearRightInsideDefault));
    m_vRearRightInsideColorBlockArray.push_back(new RearRightInsideThreeStep(REAR_RIGHT_INSIDE_THREE_STEP, TRUE, ((DefaultArea*)area)->m_pRearRightInsideDefault));
}

RearRightInside::~RearRightInside()
{
    for(auto val : m_vRearRightInsideColorBlockArray) {
        delete ((ColorBlock*)val);
    }
}

RearRightInsideDefault::RearRightInsideDefault(const string& pngResourceFile, const BOOLEAN isCalculateValidErea)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(nullptr)
{
}

void RearRightInsideDefault::CompoundArea()
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

void RearRightInsideDefault::DeCompoundArea()
{

}

RearRightInsideOneStep::RearRightInsideOneStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(area)
{

}

void RearRightInsideOneStep::CompoundArea()
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

void RearRightInsideOneStep::DeCompoundArea()
{

}

RearRightInsideTwoStep::RearRightInsideTwoStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(area)
{

}

void RearRightInsideTwoStep::CompoundArea()
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

void RearRightInsideTwoStep::DeCompoundArea()
{

}

RearRightInsideThreeStep::RearRightInsideThreeStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(area)
{

}

void RearRightInsideThreeStep::CompoundArea()
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

void RearRightInsideThreeStep::DeCompoundArea()
{

}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman