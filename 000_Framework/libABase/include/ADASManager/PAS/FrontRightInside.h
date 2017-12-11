
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_FRONTRIGHTINSIDE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_FRONTRIGHTINSIDE_H__

#include "ADASManager/PAS/RadarSenser.h"
#include "ADASManager/PAS/ColorBlock.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class FrontRightInside : public RadarSenser
{
public:
    FrontRightInside(const string& radarSenserName, BYTE* const hasCompoundedArea);

    virtual ~FrontRightInside();
};

class FrontRightInsideOneStep : public ColorBlock
{
public:
    FrontRightInsideOneStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontRightInsideTwoStep : public ColorBlock
{
public:
    FrontRightInsideTwoStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontRightInsideThreeStep : public ColorBlock
{
public:
    FrontRightInsideThreeStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontRightInsideFourStep : public ColorBlock
{
public:
    FrontRightInsideFourStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontRightInsideFiveStep : public ColorBlock
{
public:
    FrontRightInsideFiveStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontRightInsideSixStep : public ColorBlock
{
public:
    FrontRightInsideSixStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontRightInsideSevenStep : public ColorBlock
{
public:
    FrontRightInsideSevenStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontRightInsideEightStep : public ColorBlock
{
public:
    FrontRightInsideEightStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontRightInsideNineStep : public ColorBlock
{
public:
    FrontRightInsideNineStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_FRONTRIGHTINSIDE_H__