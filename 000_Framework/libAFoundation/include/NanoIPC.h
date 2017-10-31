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
    BOOLEAN send(Int32 sock, const CHAR* msg, Int32 size);
    BOOLEAN receive(Int32 sock, VOID* buff);
    VOID close(Int32 sock);
};


class SendNode
{
public:
    SendNode(const string& uri);
    ~SendNode();

    VOID create_node();
    VOID send(const string& data);
    VOID release();

private:
    NanoIPC* m_ipc;
    const string m_uri;
    Int32 m_sock;
};


class ReceiveNode
{
public:
    ReceiveNode(const string& uri);
    ~ReceiveNode();

    VOID create_node();
    VOID receive(CHAR* data);
    VOID release();

private:
    NanoIPC* m_ipc;
    const string m_uri;
    Int32 m_sock;
};


}
}
}
}





#endif