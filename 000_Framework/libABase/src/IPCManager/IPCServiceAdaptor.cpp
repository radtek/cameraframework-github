#include "IPCServiceAdaptor.h"
#include "TraceMacros.h"

using namespace Harman::Adas::AFramework::AFoundation;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace  IPCManager{

IPCServiceAdaptor::IPCServiceAdaptor()
    :m_pServiceParser(NULL)
    ,m_bIsConnected(FALSE)
{
    m_vClientParser.clear();
}

IPCServiceAdaptor::~IPCServiceAdaptor()
{

}

VOID  IPCServiceAdaptor::registerClientParser(IPCBaseParser* pParser)
{

}

VOID  IPCServiceAdaptor::registerService(IPCBaseParser* pParser)
{
    
}

}
}
}
}
}