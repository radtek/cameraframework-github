#ifndef IPC_ADAPTOR_GWMV2_H_
#define IPC_ADAPTOR_GWMV2_H_
#include "TypeDefine.h"
#include "IPCServiceAdaptor.h"

class IPCAdaptorGWMv2 : public IPCServiceAdaptor
{
public:
    static IPCAdaptorGWMv2*   getInstance();
    static VOID             deInstance();
    virtual ~IPCAdaptorGWMv2();

public:
    VOID initialize();


protected:
    IPCAdaptorGWMv2();

private:
    static IPCAdaptorGWMv2* m_pInstance;
};

#endif