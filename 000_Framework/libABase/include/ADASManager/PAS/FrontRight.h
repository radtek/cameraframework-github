
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_FRONTRIGHT_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_FRONTRIGHT_H__

#include "ADASManager/PAS/RadarSenser.h"
#include "ADASManager/PAS/ColorBlock.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class FrontRight : public RadarSenser
{
public:
    FrontRight(const string& radarSenserName, BYTE* hasCompoundedArea);

    virtual ~FrontRight();
};

class FrontRightDefault : public ColorBlock
{
public:
    FrontRightDefault(const string& pngResourceFile, BYTE* hasCompoundedArea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class FrontRightOneStep : public ColorBlock
{
public:
    FrontRightOneStep(const string& pngResourceFile, BYTE* hasCompoundedArea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class FrontRightTwoStep : public ColorBlock
{
public:
    FrontRightTwoStep(const string& pngResourceFile, BYTE* hasCompoundedArea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

class FrontRightThreeStep : public ColorBlock
{
public:
    FrontRightThreeStep(const string& pngResourceFile, BYTE* hasCompoundedArea);

    virtual void CompoundArea() override;

    virtual void DeCompoundArea() override;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_FRONTRIGHT_H__