
#include "ADASManager/PAS/FrontRight.h"
#include "ADASManager/PAS/DefaultArea.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

FrontRight::FrontRight(Area* area)
{
    m_vFrontRightColorBlockArray.push_back(((DefaultArea*)area)->m_pFrontRightDefault);
    m_vFrontRightColorBlockArray.push_back(new FrontRightOneStep(FRONT_RIGHT_ONE_STEP, TRUE, ((DefaultArea*)area)->m_pFrontRightDefault));
    m_vFrontRightColorBlockArray.push_back(new FrontRightTwoStep(FRONT_RIGHT_TWO_STEP, TRUE, ((DefaultArea*)area)->m_pFrontRightDefault));
    m_vFrontRightColorBlockArray.push_back(new FrontRightThreeStep(FRONT_RIGHT_THREE_STEP, TRUE, ((DefaultArea*)area)->m_pFrontRightDefault));
}

FrontRight::~FrontRight()
{
    for(auto val : m_vFrontRightColorBlockArray) {
        delete ((ColorBlock*)val);
    }
}

FrontRightDefault::FrontRightDefault(const string& pngResourceFile, const BOOLEAN isCalculateValidErea)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(nullptr)
{
}

void FrontRightDefault::CompoundArea()
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

void FrontRightDefault::DeCompoundArea()
{

}

FrontRightOneStep::FrontRightOneStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(area)
{

}

void FrontRightOneStep::CompoundArea()
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

void FrontRightOneStep::DeCompoundArea()
{

}

FrontRightTwoStep::FrontRightTwoStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(area)
{

}

void FrontRightTwoStep::CompoundArea()
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

void FrontRightTwoStep::DeCompoundArea()
{

}

FrontRightThreeStep::FrontRightThreeStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(area)
{

}

void FrontRightThreeStep::CompoundArea()
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

void FrontRightThreeStep::DeCompoundArea()
{

}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman