

#include "../include/CRunableBase.h"
#include <sys/syscall.h>

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

CRunableBase::CRunableBase(BOOLEAN bwaitloop)
    : m_bQuit(FALSE)
    , m_strThreadName("ThreadNameNotSet")
{
    m_pevent = new CEvent(bwaitloop);
    pause();
    m_hThread = thread{&CRunableBase::run,this};
}

static VOID CBRunnable(VOID* para)
{
    ((CRunableBase*)para)->CBPause();
};

VOID CRunableBase::CBPause()
{
    ALOGD("CBPause is default\n");
}

CRunableBase::CRunableBase(const string& strName, BOOLEAN bwaitloop)
    : m_strThreadName(strName)
    , m_bQuit(FALSE)
{
    m_pevent = new CEvent(bwaitloop, CBRunnable,(VOID*)this);
    m_pevent->setOwner(strName);
    pause();
}

CRunableBase::~CRunableBase()
{
    if(m_pevent) 
    {
        delete m_pevent;
        m_pevent = NULL;
    }

    m_hThread.detach();
}

VOID CRunableBase::run()
{
    //prctl(PR_SET_NAME, m_strThreadName.c_str());
    init();

    while( !m_bQuit )
    {
        m_pevent->wait();

        if(m_bQuit)
        {
            ALOGI("thread id = [%ld]  name = [%s]...exit1 \n ", (long int)syscall(__NR_gettid), m_strThreadName.c_str());
            return;
        }

        update();
    }

    ALOGD("thread id = [%ld]  name = [%s]...exit2 \n ", (long int)syscall(__NR_gettid), m_strThreadName.c_str());
    return;
}

VOID CRunableBase::start()
{
     m_hThread = thread{&CRunableBase::run,this};
     m_pevent->set();
}

VOID CRunableBase::quit()
{
    m_bQuit = TRUE;
    m_pevent->set();
}

VOID CRunableBase::join()
{
    m_hThread.join();
}

VOID CRunableBase::pause()
{
    m_pevent->reset();
}

VOID CRunableBase::resume()
{
    m_pevent->set();
}

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman