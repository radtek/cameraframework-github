
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_FRONTRIGHTINSIDE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_FRONTRIGHTINSIDE_H__

#include "ADASManager/PAS/ColorBlock.h"
#include "ADASManager/PAS/Area.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class FrontRightInside
{
public:
    FrontRightInside(Area* area);

    virtual ~FrontRightInside();

public:
    vector<Area*> m_vFrontRightInsideColorBlockArray;
};

class FrontRightInsideDefault : public DecoratorArea , public ColorBlock
{
public:
    FrontRightInsideDefault(const string& pngResourceFile, const BOOLEAN isCalculateValidErea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class FrontRightInsideOneStep : public DecoratorArea , public ColorBlock
{
public:
    FrontRightInsideOneStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class FrontRightInsideTwoStep : public DecoratorArea , public ColorBlock
{
public:
    FrontRightInsideTwoStep(const string& pngResourceFile, const BOOLEAN isCalculateValidErea, Area* area);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_FRONTRIGHTINSIDE_H__