
#ifdef LINUX_OS
#include "../include/CRunableBase.h"
#else
#include "..\include\CRunableBase.h"
#endif

#include <sys/prctl.h>
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

#ifdef QNX_OS
    pthread_create(&m_hThread, NULL, pthreadRunnable, this);
#endif
#ifdef LINUX_OS
    m_hThread = thread{&CRunableBase::run,this};
#endif
#ifdef WIN_OS
    m_hThread->start(pthreadRunnable,this);
#endif

    ALOGD("CRunableBase constructor\n");
}

static VOID CBRunnable(VOID* para){

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
#ifndef WIN_OS
    m_pevent = new CEvent(bwaitloop, CBRunnable,(VOID*)this);
    m_pevent->setOwner(strName);
#else
    m_pevent = new CEvent(bwaitloop);
#endif

#ifdef WIN_OS
    m_hThread = new Poco::Thread(m_strThreadName.c_str());
#endif

    pause();

#ifdef QNX_OS
    pthread_create(&m_hThread, NULL, pthreadRunnable, this);
#endif
#ifdef LINUX_OS
    m_hThread = thread{&CRunableBase::run,this};
#endif
#ifdef WIN_OS
    m_hThread->start(pthreadRunnable,this);
#endif

    ALOGD("CRunableBase constructor with name = %s\n", strName.c_str());
}

CRunableBase::~CRunableBase()
{
    if(m_pevent) {
        delete m_pevent;
        m_pevent = NULL;
    }

#ifdef WIN_OS
    if(m_hThread ) {
        delete m_hThread;
        m_hThread = NULL;
    }
#endif
#ifdef QNX_OS
    pthread_detach(m_hThread);
#endif
#ifdef LINUX_OS
    m_hThread.detach();
#endif
}

VOID CRunableBase::init()
{
    m_loopCnt = 0;
    ALOGI("default CRunableBase::init  name = %s\n ", m_strThreadName.c_str());
}

VOID CRunableBase::run()
{
    //PDCC_LOG_INFO("CRunableBase::run thread id = %d  name = %s...start\n ",0, m_strThreadName.c_str());
    prctl(PR_SET_NAME, m_strThreadName.c_str());
    init();
    while( !m_bQuit )
    {
        m_loopCnt++;
        m_pevent->wait();
        if(m_bQuit)
        {
            ALOGI("run thread id = %ld  name = %s...exit1 \n ", (long int)syscall(__NR_gettid), m_strThreadName.c_str());
            return;
        }
        update();
        if(m_loopCnt%300==0)
        {
            ALOGI("run  name = %s\n ", m_strThreadName.c_str());
        }
       //PDCC_LOG_INFO("CRunableBase::run  name = %s\n ", m_strThreadName.c_str());
    }

    ALOGD("run thread id = %ld  name = %s...exit2 \n ", (long int)syscall(__NR_gettid), m_strThreadName.c_str());
    return;
}

#ifdef QNX_OS
static VOID* pthreadRunnable(VOID* para){

    ((CRunableBase*)para)->run();
    return NULL;
};
#endif

#ifdef WIN_OS
static VOID pthreadRunnable(VOID* pData)
{
    ((CRunableBase*)pData)->run();
}
#endif

VOID CRunableBase::start()
{
    ALOGI("CRunableBase::run thread id = %ld  name = %s...start\n ",(long int)syscall(__NR_gettid), m_strThreadName.c_str());
    m_pevent->set();
}

VOID CRunableBase::quit()
{
    ALOGI("CRunableBase::run thread id = %ld  name = %s...quit\n ",(long int)syscall(__NR_gettid), m_strThreadName.c_str());
    m_bQuit = TRUE;
    m_pevent->set();
}

VOID CRunableBase::join()
{
    ALOGI("CRunableBase::run thread id = %ld  name = %s...join\n ",(long int)syscall(__NR_gettid), m_strThreadName.c_str());
#ifdef QNX_OS
    pthread_join(m_hThread, NULL);
#endif
#ifdef LINUX_OS
    m_hThread.join();
#endif
#ifdef WIN_OS
    m_hThread->join();
#endif
}

VOID CRunableBase::pause()
{
    ALOGI("CRunableBase::run thread id = %ld  name = %s...pause\n ",(long int)syscall(__NR_gettid), m_strThreadName.c_str());
    m_pevent->reset();
}

VOID CRunableBase::resume()
{
    ALOGI("CRunableBase::run thread id = %ld  name = %s...resume\n ",(long int)syscall(__NR_gettid), m_strThreadName.c_str());
    m_pevent->set();
}

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman