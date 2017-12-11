
#include "MessageForQueue.h"
#include "ADASManager/PAS/RadarSenser.h"
#include "ADASManager/PAS/PASRenderLooperThread.h"

using Harman::Adas::AFramework::AFoundation::MessageForQueue;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

ThreadPool* RadarSenser::m_pThreadPoolHolder = new ThreadPool(5);

RadarSenser::RadarSenser(const string& radarSenserName)
    : m_strRadarSenserName(radarSenserName)
{
}

RadarSenser::~RadarSenser()
{
}

VOID RadarSenser::SetHandler(PASMessageHandler* handler)
{
    m_pHandler = handler;
}

void Dojob(VOID* object, const UInt32 degree)
{
    RadarSenser* sender = (RadarSenser*)object;

    for(UInt32 i = 1; i < sender->m_vColorBlockArray.size(); i++){

        if(i < degree && (sender->m_vColorBlockArray)[i]->m_bIsDecoratored == TRUE) {
            ((sender->m_vColorBlockArray)[i])->DeCompoundArea();
        }

        if(i >= degree && (sender->m_vColorBlockArray)[i]->m_bIsDecoratored == FALSE) {
            ((sender->m_vColorBlockArray)[i])->CompoundArea();
        }
    }

    sender->m_pHandler->SendMessage(new MessageForQueue(0, 0, "test"));
}

void RadarSenser::Flush(const UInt32 degree) const
{
    std::future<void> gh = m_pThreadPoolHolder->Commit(Dojob, (VOID*)this, degree);
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman