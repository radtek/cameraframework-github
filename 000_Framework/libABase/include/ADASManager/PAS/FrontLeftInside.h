
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
    FrontLeftInside(const string& radarSenserName, BYTE* const hasCompoundedArea);

    virtual ~FrontLeftInside();
};

class FrontLeftInsideOneStep : public ColorBlock
{
public:
    FrontLeftInsideOneStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontLeftInsideTwoStep : public ColorBlock
{
public:
    FrontLeftInsideTwoStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontLeftInsideThreeStep : public ColorBlock
{
public:
    FrontLeftInsideThreeStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontLeftInsideFourStep : public ColorBlock
{
public:
    FrontLeftInsideFourStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontLeftInsideFiveStep : public ColorBlock
{
public:
    FrontLeftInsideFiveStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontLeftInsideSixStep : public ColorBlock
{
public:
    FrontLeftInsideSixStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontLeftInsideSevenStep : public ColorBlock
{
public:
    FrontLeftInsideSevenStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontLeftInsideEightStep : public ColorBlock
{
public:
    FrontLeftInsideEightStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontLeftInsideNineStep : public ColorBlock
{
public:
    FrontLeftInsideNineStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_FRONTLEFTINSIDE_H__