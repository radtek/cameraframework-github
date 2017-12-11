
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_RADARSENSER_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_RADARSENSER_H__

#include "ThreadPool.h"
#include "ADASManager/PAS/ColorBlock.h"

using Harman::Adas::AFramework::AFoundation::ThreadPool;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class PASMessageHandler;

class RadarSenser
{
public:
    RadarSenser(const string& radarSenserName);

    virtual ~RadarSenser();

    void Flush(const UInt32 degree) const;

    VOID SetHandler(PASMessageHandler* handler);

public:
    vector<ColorBlock*> m_vColorBlockArray;

    const string& m_strRadarSenserName;

    PASMessageHandler* m_pHandler = nullptr;

    static ThreadPool* m_pThreadPoolHolder;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_RADARSENSER_H__