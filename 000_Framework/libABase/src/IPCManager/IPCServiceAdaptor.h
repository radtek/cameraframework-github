#ifndef IPC_SERVICE_ADAPTOR_H_
#define IPC_SERVICE_ADAPTOR_H_
#include "TypeDefine.h"
#include "IPCService.h"
#include "IPCBaseParser.h"


namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace  IPCManager{

class  IPCServiceAdaptor
{
public:
    IPCServiceAdaptor();
    virtual ~IPCServiceAdaptor();

    VOID  registerClientParser(IPCBaseParser* pParser);
    VOID  registerService(IPCService* pParser);

protected:

private:
    IPCBaseParser*   m_pParser;
    IPCService*           m_pService;
    BOOLEAN              m_bIsConnected;

}


}//Harman
}//Adas
}//AFramework
}//ABase
}//IPCManager


#endif