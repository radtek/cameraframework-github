
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
    FrontRight(const string& radarSenserName, BYTE* const hasCompoundedArea);

    virtual ~FrontRight();
};

class FrontRightOneStep : public ColorBlock
{
public:
    FrontRightOneStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontRightTwoStep : public ColorBlock
{
public:
    FrontRightTwoStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontRightThreeStep : public ColorBlock
{
public:
    FrontRightThreeStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontRightFourStep : public ColorBlock
{
public:
    FrontRightFourStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontRightFiveStep : public ColorBlock
{
public:
    FrontRightFiveStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontRightSixStep : public ColorBlock
{
public:
    FrontRightSixStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontRightSevenStep : public ColorBlock
{
public:
    FrontRightSevenStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontRightEightStep : public ColorBlock
{
public:
    FrontRightEightStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

class FrontRightNineStep : public ColorBlock
{
public:
    FrontRightNineStep(const string& pngResourceFile, BYTE* const hasCompoundedArea);
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_FRONTRIGHT_H__