
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARLEFTINSIDE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARLEFTINSIDE_H__

#include "ADASManager/PAS/ColorBlock.h"
#include "ADASManager/PAS/Area.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class RearLeftInside
{
public:
    RearLeftInside(Area* area);

    virtual ~RearLeftInside();

public:
    vector<Area*> m_vRearLeftInsideColorBlockArray;
};

class RearLeftInsideDefault : public DecoratorArea , public ColorBlock
{
public:
    RearLeftInsideDefault(const string& pngResourceFile, const BOOLEAN isCalculateValidErea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearLeftInsideOneStep : public DecoratorArea , public ColorBlock
{
public:
    RearLeftInsideOneStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearLeftInsideTwoStep : public DecoratorArea , public ColorBlock
{
public:
    RearLeftInsideTwoStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearLeftInsideThreeStep : public DecoratorArea , public ColorBlock
{
public:
    RearLeftInsideThreeStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARLEFTINSIDE_H__