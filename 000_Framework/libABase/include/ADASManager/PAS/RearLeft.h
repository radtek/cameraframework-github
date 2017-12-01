
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARLEFT_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARLEFT_H__

#include "ADASManager/PAS/RadarSenser.h"
#include "ADASManager/PAS/ColorBlock.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class RearLeft : public RadarSenser
{
public:
    RearLeft(const string& radarSenserName, BYTE* hasCompoundedArea);

    virtual ~RearLeft();
};

class RearLeftDefault : public ColorBlock
{
public:
    RearLeftDefault(const string& pngResourceFile, BYTE* hasCompoundedArea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearLeftOneStep : public ColorBlock
{
public:
    RearLeftOneStep(const string& pngResourceFile, BYTE* hasCompoundedArea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearLeftTwoStep : public ColorBlock
{
public:
    RearLeftTwoStep(const string& pngResourceFile, BYTE* hasCompoundedArea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearLeftThreeStep : public ColorBlock
{
public:
    RearLeftThreeStep(const string& pngResourceFile, BYTE* hasCompoundedArea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearLeftFourStep : public ColorBlock
{
public:
    RearLeftFourStep(const string& pngResourceFile, BYTE* hasCompoundedArea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearLeftFiveStep : public ColorBlock
{
public:
    RearLeftFiveStep(const string& pngResourceFile, BYTE* hasCompoundedArea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class RearLeftSixStep : public ColorBlock
{
public:
    RearLeftSixStep(const string& pngResourceFile, BYTE* hasCompoundedArea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARLEFT_H__