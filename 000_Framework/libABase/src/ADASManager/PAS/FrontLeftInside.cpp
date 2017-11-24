
#include "ADASManager/PAS/FrontLeftInside.h"
#include "ADASManager/PAS/DefaultArea.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

FrontLeftInside::FrontLeftInside(Area* area)
{
    m_vFrontLeftInsideColorBlockArray.push_back(((DefaultArea*)area)->m_pFrontLeftInsideDefault);
    m_vFrontLeftInsideColorBlockArray.push_back(new FrontLeftInsideOneStep(FRONT_LEFT_INSIDE_ONE_STEP, TRUE, ((DefaultArea*)area)->m_pFrontLeftInsideDefault));
    m_vFrontLeftInsideColorBlockArray.push_back(new FrontLeftInsideTwoStep(FRONT_LEFT_INSIDE_TWO_STEP, TRUE, ((DefaultArea*)area)->m_pFrontLeftInsideDefault));
}

FrontLeftInside::~FrontLeftInside()
{
    for(auto val : m_vFrontLeftInsideColorBlockArray) {
        delete ((ColorBlock*)val);
    }
}

FrontLeftInsideDefault::FrontLeftInsideDefault(const string& pngResourceFile, const BOOLEAN isCalculateValidErea)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(nullptr)
{
}

void FrontLeftInsideDefault::CompoundArea()
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

void FrontLeftInsideDefault::DeCompoundArea()
{

}

FrontLeftInsideOneStep::FrontLeftInsideOneStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(area)
{

}

void FrontLeftInsideOneStep::CompoundArea()
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

void FrontLeftInsideOneStep::DeCompoundArea()
{

}

FrontLeftInsideTwoStep::FrontLeftInsideTwoStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(area)
{

}

void FrontLeftInsideTwoStep::CompoundArea()
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

void FrontLeftInsideTwoStep::DeCompoundArea()
{

}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman