
#ifndef __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_OBSERVER_H__
#define __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_OBSERVER_H__

#include "TypeDefine.h"
#include "platformdef.h"
#include "TraceMacros.h"

using namespace std;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

class Subject;

class Observer
{
public:
    Observer(const string& name)
        : m_strObserverName(name)
    {}

    virtual VOID Update(Subject* subject, Int32 state) = 0;

    const string GetObserverName() { return m_strObserverName; }

    virtual ~Observer() {}

protected:
    const string m_strObserverName;
};

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_OBSERVER_H__