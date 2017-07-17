#include "IPCAdaptorGWMv2.h"
#include "IPCImplGWMv2.h"

IPCAdaptorGWMv2* IPCAdaptorGWMv2::m_pInstance = NULL;

IPCAdaptorGWMv2* IPCAdaptorGWMv2::getInstance()
{
    if(m_pInstance == NULL) {
        m_pInstance = new IPCAdaptorGWMv2();
    }
    return m_pInstance;
}

VOID IPCAdaptorGWMv2::deInstance()
{
   if(m_pInstance != NULL)
   {
      delete m_pInstance;
      m_pInstance = NULL;
   }
}

IPCAdaptorGWMv2::IPCAdaptorGWMv2()
{

}

IPCAdaptorGWMv2::~IPCAdaptorGWMv2()
{

}

VOID IPCAdaptorGWMv2::initialize()
{
    registerService((IPCService*)new IPCImplGWMv2());
}

