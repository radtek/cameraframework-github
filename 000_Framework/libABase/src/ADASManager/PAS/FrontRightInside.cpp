
#include "ADASManager/PAS/FrontRightInside.h"
#include "ADASManager/PAS/DefaultArea.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

FrontRightInside::FrontRightInside(Area* area)
{
    m_vFrontRightInsideColorBlockArray.push_back(((DefaultArea*)area)->m_pFrontRightInsideDefault);
    m_vFrontRightInsideColorBlockArray.push_back(new FrontRightInsideOneStep(FRONT_RIGHT_INSIDE_ONE_STEP, TRUE, ((DefaultArea*)area)->m_pFrontRightInsideDefault));
    m_vFrontRightInsideColorBlockArray.push_back(new FrontRightInsideTwoStep(FRONT_RIGHT_INSIDE_TWO_STEP, TRUE, ((DefaultArea*)area)->m_pFrontRightInsideDefault));
}

FrontRightInside::~FrontRightInside()
{
    for(auto val : m_vFrontRightInsideColorBlockArray) {
        delete ((ColorBlock*)val);
    }
}

FrontRightInsideDefault::FrontRightInsideDefault(const string& pngResourceFile, const BOOLEAN isCalculateValidErea)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(nullptr)
{
}

void FrontRightInsideDefault::CompoundArea()
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

void FrontRightInsideDefault::DeCompoundArea()
{

}

FrontRightInsideOneStep::FrontRightInsideOneStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(area)
{

}

void FrontRightInsideOneStep::CompoundArea()
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

void FrontRightInsideOneStep::DeCompoundArea()
{

}

FrontRightInsideTwoStep::FrontRightInsideTwoStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(area)
{

}

void FrontRightInsideTwoStep::CompoundArea()
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

void FrontRightInsideTwoStep::DeCompoundArea()
{

}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman