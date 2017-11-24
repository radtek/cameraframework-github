
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_FRONTLEFTINSIDE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_FRONTLEFTINSIDE_H__

#include "ADASManager/PAS/ColorBlock.h"
#include "ADASManager/PAS/Area.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class FrontLeftInside
{
public:
    FrontLeftInside(Area* area);

    virtual ~FrontLeftInside();

public:
    vector<Area*> m_vFrontLeftInsideColorBlockArray;
};

class FrontLeftInsideDefault : public DecoratorArea , public ColorBlock
{
public:
    FrontLeftInsideDefault(const string& pngResourceFile, const BOOLEAN isCalculateValidErea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class FrontLeftInsideOneStep : public DecoratorArea , public ColorBlock
{
public:
    FrontLeftInsideOneStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class FrontLeftInsideTwoStep : public DecoratorArea , public ColorBlock
{
public:
    FrontLeftInsideTwoStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_FRONTLEFTINSIDE_H__