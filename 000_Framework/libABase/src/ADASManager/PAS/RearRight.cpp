
#include "ADASManager/PAS/RearRight.h"
#include "ADASManager/PAS/DefaultArea.h"
#include "ADASManager/PAS/ResourcePngDefine.h"

//#include "ADASManager/PAS/GraphicCore/PasUtils.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

RearRight::RearRight(Area* area)
{
    m_vRearRightColorBlockArray.push_back(((DefaultArea*)area)->m_pRearRightDefault);
    m_vRearRightColorBlockArray.push_back(new RearRightOneStep(REAR_RIGHT_ONE_STEP, TRUE, ((DefaultArea*)area)->m_pRearRightDefault));
    m_vRearRightColorBlockArray.push_back(new RearRightTwoStep(REAR_RIGHT_TWO_STEP, TRUE, ((DefaultArea*)area)->m_pRearRightDefault));
    m_vRearRightColorBlockArray.push_back(new RearRightThreeStep(REAR_RIGHT_THREE_STEP, TRUE, ((DefaultArea*)area)->m_pRearRightDefault));
    m_vRearRightColorBlockArray.push_back(new RearRightFourStep(REAR_RIGHT_FOUR_STEP, TRUE, ((DefaultArea*)area)->m_pRearRightDefault));
    m_vRearRightColorBlockArray.push_back(new RearRightFiveStep(REAR_RIGHT_FIVE_STEP, TRUE, ((DefaultArea*)area)->m_pRearRightDefault));
    m_vRearRightColorBlockArray.push_back(new RearRightSixStep(REAR_RIGHT_SIX_STEP, TRUE, ((DefaultArea*)area)->m_pRearRightDefault));

    // IMAGEINFO imageinfo;
    // imageinfo.height = 152;
    // imageinfo.width = 228;
    // imageinfo.image_size = 152*228*4;
    // RearRightSixStep* tmp = (RearRightSixStep*)(m_vRearRightColorBlockArray[6]);
    // ColorBlock* tmp2 = (ColorBlock*)tmp;
    // PasUtils::SaveAsBmp("/usr/bin/snowback.bmp", (void*)(tmp2->m_pColorBlockBuffer), imageinfo);
}

RearRight::~RearRight()
{
    for(auto val : m_vRearRightColorBlockArray) {
        delete ((ColorBlock*)val);
    }
}

RearRightDefault::RearRightDefault(const string& pngResourceFile, const BOOLEAN isCalculateValidErea)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(nullptr)
{
}

void RearRightDefault::CompoundArea()
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

void RearRightDefault::DeCompoundArea()
{

}

RearRightOneStep::RearRightOneStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(area)
{

}

void RearRightOneStep::CompoundArea()
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

void RearRightOneStep::DeCompoundArea()
{

}

RearRightTwoStep::RearRightTwoStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(area)
{

}

void RearRightTwoStep::CompoundArea()
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

void RearRightTwoStep::DeCompoundArea()
{

}

RearRightThreeStep::RearRightThreeStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(area)
{

}

void RearRightThreeStep::CompoundArea()
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

void RearRightThreeStep::DeCompoundArea()
{

}

RearRightFourStep::RearRightFourStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(area)
{

}

void RearRightFourStep::CompoundArea()
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

void RearRightFourStep::DeCompoundArea()
{

}

RearRightFiveStep::RearRightFiveStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(area)
{

}

void RearRightFiveStep::CompoundArea()
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

void RearRightFiveStep::DeCompoundArea()
{

}

RearRightSixStep::RearRightSixStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area)
    : ColorBlock(pngResourceFile, isCalculateValidErea)
    , DecoratorArea(area)
{

}

void RearRightSixStep::CompoundArea()
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

void RearRightSixStep::DeCompoundArea()
{

}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman