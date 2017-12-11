
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARRIGHT_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARRIGHT_H__

#include "ADASManager/PAS/RadarSenser.h"
#include "ADASManager/PAS/ColorBlock.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class RearRight : public RadarSenser
{
public:
    RearRight(const string& radarSenserName, BYTE* const hasCompoundedArea);

    virtual ~RearRight();
};

class RearRightOneStep : public ColorBlock
{
public:
    RearRightOneStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearRightTwoStep : public ColorBlock
{
public:
    RearRightTwoStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearRightThreeStep : public ColorBlock
{
public:
    RearRightThreeStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearRightFourStep : public ColorBlock
{
public:
    RearRightFourStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearRightFiveStep : public ColorBlock
{
public:
    RearRightFiveStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearRightSixStep : public ColorBlock
{
public:
    RearRightSixStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearRightSevenStep : public ColorBlock
{
public:
    RearRightSevenStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearRightEightStep : public ColorBlock
{
public:
    RearRightEightStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearRightNineStep : public ColorBlock
{
public:
    RearRightNineStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARRIGHT_H__