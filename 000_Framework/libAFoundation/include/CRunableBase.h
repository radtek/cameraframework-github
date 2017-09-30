
#ifndef __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CRunableBase_H__
#define __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CRunableBase_H__

#include "platformdef.h"
#include "stdio.h"
#include "TraceMacros.h"

#ifdef WIN_OS
typedef Poco::Event CEvent;
#else
#include "CEvent.h"
#endif

using namespace std;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

class CRunableBase
{
public:
    CRunableBase(BOOLEAN bwaitloop);
    virtual ~CRunableBase();
    CRunableBase(const string& strName, BOOLEAN bwaitloop);
    virtual VOID start();
    virtual VOID start(VOID* pData){;}
    virtual VOID quit();
    virtual VOID join();
    virtual VOID init();
    virtual VOID run();
    virtual VOID pause();
    virtual VOID resume();
    virtual VOID update() = 0;
    virtual VOID CBPause();

private:
#ifdef QNX_OS
    pthread_t m_hThread;
#endif
#ifdef LINUX_OS
    thread m_hThread;
#endif
#ifdef WIN_OS
    Poco::Thread* m_hThread;
#endif
    BOOLEAN m_bQuit ;
    CEvent* m_pevent;
    string m_strThreadName ;
    UInt32 m_loopCnt ;
};

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif  // __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CRunableBase_H__