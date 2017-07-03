#include <cstdlib>
#include <iostream>
#include "ServerSocket.h"
#include <time.h>
using namespace std;
// 返回自系统开机以来的毫秒数（tick）
extern unsigned long getTickCount();
#define SOCKET_RECONNECT_TIMER  10
int main(int argc, char *argv[]) {
	printf("CaseClient service start!! \n");
	/*CAdasServerSocket newsock = CAdasServerSocket();
	newsock.acceptConnect();
	while(true){
		newsock.SocketRecv();
	}
*/
	//unsigned int uiStartTime =0; //getTickCount();
	//unsigned int uiStopTime =0;

	CAdasSocketManager * SockManager = CAdasSocketManager::getInstance();
	SockManager->CAdasAcceptConnect();

	string newcommand;
	int iCntSocketNeedReConnect =0;
    while(1)//todo , start/stop thread by PC end
    {
        newcommand = SockManager->CAdasRecvCommand();
        if((""!=newcommand)&&(newcommand.size()>=1))
        {
			SockManager->CAdasParseXML(newcommand);
			//debug dump received string to console
			//printf("%s",SockManager->dumpstr().c_str());
			//loop back to client as debug purpose
			//send back is only used in callback mode - system call mode need trace client
			//SockManager->CAdasSendResult(SockManager->dumpstr().c_str());
			//run test cases
			SockManager->CAdasExcuteCommand();
			//debug, send sync to lunch next case
			SockManager->CAdasSendResult("CaseClient on Target Board is idle");
        }
        else
        {
        	iCntSocketNeedReConnect++;
        	if(SOCKET_RECONNECT_TIMER<iCntSocketNeedReConnect)
        	{
        		//block on socket reconnection
        		printf("reconnect launched! wait client coming up ...\n");
        		SockManager->CAdasAcceptConnect();
        		iCntSocketNeedReConnect =0;
        	}
        	usleep(10000);
        }
    }

	printf("exit case socket server~~~~~~~~~~ \n");
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
