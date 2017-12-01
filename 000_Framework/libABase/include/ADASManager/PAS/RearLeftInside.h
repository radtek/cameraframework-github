
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARLEFTINSIDE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARLEFTINSIDE_H__

#include "ADASManager/PAS/RadarSenser.h"
#include "ADASManager/PAS/ColorBlock.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class RearLeftInside : public RadarSenser
{
public:
    RearLeftInside(const string& radarSenserName, BYTE* hasCompoundedArea);

    virtual ~RearLeftInside();
};

class RearLeftInsideDefault : public ColorBlock
{
public:
    RearLeftInsideDefault(const string& pngResourceFile, BYTE* hasCompoundedArea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearLeftInsideOneStep : public ColorBlock
{
public:
    RearLeftInsideOneStep(const string& pngResourceFile, BYTE* hasCompoundedArea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearLeftInsideTwoStep : public ColorBlock
{
public:
    RearLeftInsideTwoStep(const string& pngResourceFile, BYTE* hasCompoundedArea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearLeftInsideThreeStep : public ColorBlock
{
public:
    RearLeftInsideThreeStep(const string& pngResourceFile, BYTE* hasCompoundedArea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARLEFTINSIDE_H__