
#ifndef __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_SUBJECT_H__
#define __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_SUBJECT_H__

#include "Observer.h"
#include "TraceMacros.h"

#include <iostream>
#include <set>

using namespace std;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

class Subject
{
public:
    virtual VOID Attach(Observer* observer) {
        m_setObservers.insert(observer);
        ALOGI("Attach Observer : %s to Subject : %s success !\n", observer->GetObserverName().c_str(), GetSubjectName().c_str());
    }

    virtual VOID Detach(Observer* observer) {
        m_setObservers.erase(m_setObservers.find(observer));
        ALOGI("Detach Observer : %s from Subject : %s success !\n", observer->GetObserverName().c_str(), GetSubjectName().c_str());
    }

    virtual VOID Notify(Int32 status) {
        ALOGI("Subject : %s begin to Notify %d Observers, contains : \n", GetSubjectName().c_str(), (UInt32)m_setObservers.size());
        Int32 i = 0;
        for (auto it : m_setObservers) {
            ALOGI("Observers[%d] : %s\n",i++, it->GetObserverName().c_str());
        }

        for (auto it : m_setObservers) {
            it->Update(this, status);
        }
    }

    const string GetSubjectName() { return m_strSubjectName; }

    virtual ~Subject() {}

protected:
    Subject(const string& name)
        : m_strSubjectName(name)
    {}

protected:
    const string m_strSubjectName;

private:
    set<Observer*> m_setObservers;
};

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_SUBJECT_H__