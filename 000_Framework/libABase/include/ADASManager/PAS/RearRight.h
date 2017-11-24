
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARRIGHT_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARRIGHT_H__

#include "ADASManager/PAS/ColorBlock.h"
#include "ADASManager/PAS/Area.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class RearRight
{
public:
    RearRight(Area* area);

    virtual ~RearRight();

public:
    vector<Area*> m_vRearRightColorBlockArray;
};

class RearRightDefault : public DecoratorArea , public ColorBlock
{
public:
    RearRightDefault(const string& pngResourceFile, const BOOLEAN isCalculateValidErea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearRightOneStep : public DecoratorArea , public ColorBlock
{
public:
    RearRightOneStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearRightTwoStep : public DecoratorArea , public ColorBlock
{
public:
    RearRightTwoStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearRightThreeStep : public DecoratorArea , public ColorBlock
{
public:
    RearRightThreeStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearRightFourStep : public DecoratorArea , public ColorBlock
{
public:
    RearRightFourStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearRightFiveStep : public DecoratorArea , public ColorBlock
{
public:
    RearRightFiveStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearRightSixStep : public DecoratorArea , public ColorBlock
{
public:
    RearRightSixStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARRIGHT_H__