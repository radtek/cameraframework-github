
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
    RearLeft(const string& radarSenserName, BYTE* const hasCompoundedArea);

    virtual ~RearLeft();
};

class RearLeftOneStep : public ColorBlock
{
public:
    RearLeftOneStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearLeftTwoStep : public ColorBlock
{
public:
    RearLeftTwoStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearLeftThreeStep : public ColorBlock
{
public:
    RearLeftThreeStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearLeftFourStep : public ColorBlock
{
public:
    RearLeftFourStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearLeftFiveStep : public ColorBlock
{
public:
    RearLeftFiveStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearLeftSixStep : public ColorBlock
{
public:
    RearLeftSixStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearLeftSevenStep : public ColorBlock
{
public:
    RearLeftSevenStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearLeftEightStep : public ColorBlock
{
public:
    RearLeftEightStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearLeftNineStep : public ColorBlock
{
public:
    RearLeftNineStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARLEFT_H__