
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARRIGHTINSIDE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARRIGHTINSIDE_H__

#include "ADASManager/PAS/RadarSenser.h"
#include "ADASManager/PAS/ColorBlock.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class RearRightInside : public RadarSenser
{
public:
    RearRightInside(const string& radarSenserName, BYTE* const hasCompoundedArea);

    virtual ~RearRightInside();
};

class RearRightInsideOneStep : public ColorBlock
{
public:
    RearRightInsideOneStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearRightInsideTwoStep : public ColorBlock
{
public:
    RearRightInsideTwoStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearRightInsideThreeStep : public ColorBlock
{
public:
    RearRightInsideThreeStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearRightInsideFourStep : public ColorBlock
{
public:
    RearRightInsideFourStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearRightInsideFiveStep : public ColorBlock
{
public:
    RearRightInsideFiveStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearRightInsideSixStep : public ColorBlock
{
public:
    RearRightInsideSixStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearRightInsideSevenStep : public ColorBlock
{
public:
    RearRightInsideSevenStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearRightInsideEightStep : public ColorBlock
{
public:
    RearRightInsideEightStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class RearRightInsideNineStep : public ColorBlock
{
public:
    RearRightInsideNineStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_REARRIGHTINSIDE_H__