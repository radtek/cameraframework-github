#ifndef _SERVERSOCKET_H_
#define _SERVERSOCKET_H_
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <queue>
#include <string>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "netdb.h"  
#include "netinet/in.h"

using namespace std;


namespace Harman {
namespace Adas {
namespace AFramework {
namespace CaseClient {

class CCommonSocket{

public:
	CCommonSocket(const char* sIP, int iPort, bool bIsServMode );
	~CCommonSocket();
	int setupEnv();
	int acceptConnect();
	//void ReConnect();
	void Disconnect();
	int SocketSend(string text);
	string SocketRecv();
	//void SetPortNum (unsigned short portnum);
	bool bIsConnected() {return m_SocketConnected; };
	int iTryConnect(); //clent mode only
private:
	int iLocalSocet;
	int iRemoteSocket;
	struct sockaddr_in m_sLocalAddr; 
	struct sockaddr_in m_sRemoteAddr; 
	unsigned short PortNum;  
	bool m_SocketConnected;	
	bool m_bIsServerMode;
	int iTryBind(); //server mode only
	char* m_pbuffer;
};

} // namespace CaseClient
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif

