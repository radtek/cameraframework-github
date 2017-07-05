#include <cstdlib>
#include <iostream>
#include <time.h>

#if 1
#include "CaseClientDeamon.h"
#include "CaseLogCollector.h"


using namespace std;
#define SOCKET_DEAMON_ADDRESS "0.0.0.0"
#define SOCKET_DEAMON_PORT 8888
#define SOCKET_IPC_ADDRESS "127.0.0.1"
#define SOCKET_IPC_PORT 8881


// ������ϵͳ���������ĺ�������tick��
extern unsigned long getTickCount();
#endif
int main(int argc, char *argv[]) {
	printf("CaseClient service start!!  222 \n");
	//while(1)
	//{
		;//sleep(1);
	//}
	/*CCommonSocket newsock = CCommonSocket();
	newsock.acceptConnect();
	while(true){
		newsock.SocketRecv();
	}
*/
	//unsigned int uiStartTime =0; //getTickCount();
	//unsigned int uiStopTime =0;
#if 1	
	CCaseLogCollector::getInstance()->vSetupCollector(SOCKET_DEAMON_ADDRESS, SOCKET_IPC_PORT);
	sleep(1);
	CCaseClientDeamon::getInstance()->vSetupCaseClientDeamon(SOCKET_DEAMON_ADDRESS, SOCKET_DEAMON_PORT);
	sleep(1);
	CCaseLogCollector::getInstance()->start();
	sleep(1); // a possible bug on multi creation
	CCaseClientDeamon::getInstance()->start();
	CCaseLogCollector::getInstance()->join();
	CCaseClientDeamon::getInstance()->join();

	printf("exit case client deamon~~~~~~~~~~ \n");
#endif	
	return EXIT_SUCCESS;
}

#if 0
/*filename:gethostbyname.c*/
#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <string>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "netdb.h"
#include "netinet/in.h"
#include "tinyxml2.h"

int main(int argc, char **argv)
{
    char *ptr, **pptr;
    struct hostent *hptr;
    char str[32];
    ptr = argv[1];

    if((hptr = gethostbyname("test")) == NULL)
    {
        printf(" gethostbyname error for host:%s\n", ptr);
        return 0;
    }

    printf("official hostname:%s\n",hptr->h_name);
    for(pptr = hptr->h_aliases; *pptr != NULL; pptr++)
        printf(" alias:%s\n",*pptr);

    switch(hptr->h_addrtype)
    {
        case AF_INET:
            for(pptr = hptr->h_addr_list; *pptr != NULL; pptr++){
                inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str));
                printf(" address:%s\n",str);
            }
            inet_ntop(hptr->h_addrtype, hptr->h_addr, str, sizeof(str));
            printf(" first address: %s\n",str);
            break;
        default:
            printf("unknown address type\n");
        break;
    }

    return 0;
}
#endif