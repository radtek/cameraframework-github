
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARLEFT_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARLEFT_H__

#include "ADASManager/PAS/ColorBlock.h"
#include "ADASManager/PAS/Area.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class RearLeft
{
public:
    RearLeft(Area* area);

    virtual ~RearLeft();

public:
    vector<Area*> m_vRearLeftColorBlockArray;
};

class RearLeftDefault : public DecoratorArea , public ColorBlock
{
public:
    RearLeftDefault(const string& pngResourceFile, const BOOLEAN isCalculateValidErea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearLeftOneStep : public DecoratorArea , public ColorBlock
{
public:
    RearLeftOneStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearLeftTwoStep : public DecoratorArea , public ColorBlock
{
public:
    RearLeftTwoStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearLeftThreeStep : public DecoratorArea , public ColorBlock
{
public:
    RearLeftThreeStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearLeftFourStep : public DecoratorArea , public ColorBlock
{
public:
    RearLeftFourStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearLeftFiveStep : public DecoratorArea , public ColorBlock
{
public:
    RearLeftFiveStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearLeftSixStep : public DecoratorArea , public ColorBlock
{
public:
    RearLeftSixStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARLEFT_H__