#ifndef __HARMAN_ADAS_AFOUNDATION_NANOIPC_H__
#define __HARMAN_ADAS_AFOUNDATION_NANOIPC_H__

#include "nanomsg/nn.h"
#include "nanomsg/pipeline.h"
#include "TypeDefine.h"

using namespace std;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

enum eIPCMode
{
    SEND,
    RECEIVE
};

class NanoIPC
{
public:
    NanoIPC() {};
    ~NanoIPC(){};

    Int32 connect(eIPCMode mode, const string& uri);
    VOID send();
    VOID listener();
    VOID close();
};


class SendNode
{
public:
    SendNode(const string& uri);
    ~SendNode();

    VOID create_node();
    VOID send(const string& Data);
    VOID release();

private:
    NanoIPC* m_ipc;
};


class ReceiveNode
{
public:
    ReceiveNode(const string& uri);
    ~ReceiveNode();

    VOID create_node();
    VOID receive();
    VOID release();

private:
    NanoIPC* m_ipc;
};


}
}
}
}





#endif