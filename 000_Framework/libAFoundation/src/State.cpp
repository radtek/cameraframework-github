
#ifdef LINUX_OS
#include "../include/State.h"
#include "../include/TraceMacros.h"
#else
#include "..\include\State.h"
#include "..\include\TraceMacros.h"
#endif

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

VOID State::Enter() const
{
    ALOGI("Enter state : %s !\n", GetStateName().c_str());
}

VOID State::Exit() const
{
    ALOGI("Exit state : %s !\n", GetStateName().c_str());
}

BOOLEAN State::ProcessMessage(UInt32 uiType, UInt32 uiID, const string& pData) const
{
    ALOGI("ProcessMessage : message id = %u !\n", uiID);
    return FALSE;
}

const string& State::GetStateName() const
{
    return m_strStateName;
}

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman