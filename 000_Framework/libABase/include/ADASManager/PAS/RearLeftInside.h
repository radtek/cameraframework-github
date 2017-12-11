
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
    RearLeftInside(const string& radarSenserName, BYTE* const hasCompoundedArea);

    virtual ~RearLeftInside();
};

class RearLeftInsideOneStep : public ColorBlock
{
public:
    RearLeftInsideOneStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearLeftInsideTwoStep : public ColorBlock
{
public:
    RearLeftInsideTwoStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearLeftInsideThreeStep : public ColorBlock
{
public:
    RearLeftInsideThreeStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearLeftInsideFourStep : public ColorBlock
{
public:
    RearLeftInsideFourStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearLeftInsideFiveStep : public ColorBlock
{
public:
    RearLeftInsideFiveStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearLeftInsideSixStep : public ColorBlock
{
public:
    RearLeftInsideSixStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearLeftInsideSevenStep : public ColorBlock
{
public:
    RearLeftInsideSevenStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearLeftInsideEightStep : public ColorBlock
{
public:
    RearLeftInsideEightStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearLeftInsideNineStep : public ColorBlock
{
public:
    RearLeftInsideNineStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARLEFTINSIDE_H__