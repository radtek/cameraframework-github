
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_FRONTLEFTINSIDE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_FRONTLEFTINSIDE_H__

#include "ADASManager/PAS/RadarSenser.h"
#include "ADASManager/PAS/ColorBlock.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class FrontLeftInside : public RadarSenser
{
public:
    FrontLeftInside(const string& radarSenserName, BYTE* hasCompoundedArea);

    virtual ~FrontLeftInside();
};

class FrontLeftInsideDefault : public ColorBlock
{
public:
    FrontLeftInsideDefault(const string& pngResourceFile, BYTE* hasCompoundedArea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class FrontLeftInsideOneStep : public ColorBlock
{
public:
    FrontLeftInsideOneStep(const string& pngResourceFile, BYTE* hasCompoundedArea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class FrontLeftInsideTwoStep : public ColorBlock
{
public:
    FrontLeftInsideTwoStep(const string& pngResourceFile, BYTE* hasCompoundedArea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_FRONTLEFTINSIDE_H__