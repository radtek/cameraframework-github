
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
    FrontLeft(const string& radarSenserName, BYTE* const hasCompoundedArea);

    ~FrontLeft();
};

class FrontLeftOneStep : public ColorBlock
{
public:
    FrontLeftOneStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontLeftTwoStep : public ColorBlock
{
public:
    FrontLeftTwoStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontLeftThreeStep : public ColorBlock
{
public:
    FrontLeftThreeStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontLeftFourStep : public ColorBlock
{
public:
    FrontLeftFourStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontLeftFiveStep : public ColorBlock
{
public:
    FrontLeftFiveStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontLeftSixStep : public ColorBlock
{
public:
    FrontLeftSixStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontLeftSevenStep : public ColorBlock
{
public:
    FrontLeftSevenStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontLeftEightStep : public ColorBlock
{
public:
    FrontLeftEightStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontLeftNineStep : public ColorBlock
{
public:
    FrontLeftNineStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_FRONTLEFT_H__