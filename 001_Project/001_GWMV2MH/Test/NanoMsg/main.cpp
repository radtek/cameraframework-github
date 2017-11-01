#include <iostream>
#include <memory>
#include <unistd.h>

#include <map>

#include "AFoundation.h"

using namespace std;
using namespace Harman::Adas::AFramework::AFoundation;

#define NODE0 "node0"
#define NODE1 "node1"


class SendNodeTest : public SendNode
{
public:
    SendNodeTest(const string& uri)
        :SendNode(uri)
    {

    }

    ~SendNodeTest(){};

private:

    
};

class ReceiveNodeTest : public ReceiveNode
{
public:
    ReceiveNodeTest(const string& uri)
        :ReceiveNode(uri)
    {

    }

    ~ReceiveNodeTest(){};

private:

};

int main(int argc, char** argv)
{
#ifdef DLTLOG
    PRINTINIT;
#endif
    
    if(strncmp (NODE0, argv[1], strlen (NODE0)) == 0)
    {
        SendNodeTest* node0 = new SendNodeTest(string("ipc:///tmp/sendNodeMsg.ipc"));
        node0->create_node();

        node0->send(string("hello fking world"));

        node0->release();
    }

    if(strncmp (NODE1, argv[1], strlen (NODE0)) == 0)
    {
        ReceiveNodeTest* node1 = new ReceiveNodeTest(string("ipc:///tmp/sendNodeMsg.ipc"));
        node1->create_node();
        CHAR data[1024] = {0};
        while(1)
        {
            Int32 bytes = node1->receive(data);
            // data[bytes] = '\0';
            printf("reveive [%d]bytes  data[%s]\n", bytes, data);

            usleep(50000);
        }

        node1->release();
    }
    
    //main thread wait here
    getchar();

#ifdef DLTLOG
    PRINTDEINIT;
#endif

    return 0;
}