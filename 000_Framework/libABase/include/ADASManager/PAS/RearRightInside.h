
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARRIGHTINSIDE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARRIGHTINSIDE_H__

#include "ADASManager/PAS/ColorBlock.h"
#include "ADASManager/PAS/Area.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class RearRightInside
{
public:
    RearRightInside(Area* area);

    virtual ~RearRightInside();

public:
    vector<Area*> m_vRearRightInsideColorBlockArray;
};

class RearRightInsideDefault : public DecoratorArea , public ColorBlock
{
public:
    RearRightInsideDefault(const string& pngResourceFile, const BOOLEAN isCalculateValidErea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearRightInsideOneStep : public DecoratorArea , public ColorBlock
{
public:
    RearRightInsideOneStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearRightInsideTwoStep : public DecoratorArea , public ColorBlock
{
public:
    RearRightInsideTwoStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearRightInsideThreeStep : public DecoratorArea , public ColorBlock
{
public:
    RearRightInsideThreeStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARRIGHTINSIDE_H__