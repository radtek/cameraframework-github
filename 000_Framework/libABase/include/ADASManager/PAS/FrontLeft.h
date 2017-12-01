
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_FRONTLEFT_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_FRONTLEFT_H__

#include "ADASManager/PAS/RadarSenser.h"
#include "ADASManager/PAS/ColorBlock.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class FrontLeft : public RadarSenser
{
public:
    FrontLeft(const string& radarSenserName, BYTE* hasCompoundedArea);

    virtual ~FrontLeft();
};

class FrontLeftDefault : public ColorBlock
{
public:
    FrontLeftDefault(const string& pngResourceFile, BYTE* hasCompoundedArea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class FrontLeftOneStep : public ColorBlock
{
public:
    FrontLeftOneStep(const string& pngResourceFile, BYTE* hasCompoundedArea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class FrontLeftTwoStep : public ColorBlock
{
public:
    FrontLeftTwoStep(const string& pngResourceFile, BYTE* hasCompoundedArea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class FrontLeftThreeStep : public ColorBlock
{
public:
    FrontLeftThreeStep(const string& pngResourceFile, BYTE* hasCompoundedArea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_FRONTLEFT_H__