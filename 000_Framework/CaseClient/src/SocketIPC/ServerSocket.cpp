#include "ServerSocket.h" 
#include <sys/socket.h>
#include <sys/time.h>

namespace Harman {
namespace Adas {
namespace AFramework {
namespace CaseClient {

#define BUFSIZE 40960*10

//------------------------------CCommonSocket-------------------------------------
//------------------------------------------------------------------------------------

CCommonSocket::~CCommonSocket()
{
    close(iLocalSocet);
    delete [] m_pbuffer;
}

CCommonSocket::CCommonSocket(const char* sIP, int iPort, bool bIsServer)
: m_SocketConnected(false)
, m_bIsServerMode(false)
{
	m_pbuffer = new char[BUFSIZE];
	//set a tmp host name for case client auto connection
	m_bIsServerMode = bIsServer;
	int ierr=system("hostname CaseClientVersion001");
	if(ierr)
	{
		printf("set hostname as CaseClientVersion001 failed !\n");
	}
	else
	{
		printf("set hostname as CaseClientVersion001 successed !\n");
	}
	PortNum = iPort;

	iLocalSocet = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(-1 == iLocalSocet)
	{
	    printf("socket fail !\n");
	}
	memset(&m_sLocalAddr,0,sizeof(m_sLocalAddr));
	memset(&m_sRemoteAddr,0,sizeof(m_sRemoteAddr));

	if(m_bIsServerMode) 
	{
		m_sLocalAddr.sin_family=AF_INET;
		m_sLocalAddr.sin_addr.s_addr= inet_addr(sIP);
		m_sLocalAddr.sin_port=htons(PortNum);
	}
	else
	{
		m_sRemoteAddr.sin_family=AF_INET;
		m_sRemoteAddr.sin_addr.s_addr= inet_addr(sIP);
		m_sRemoteAddr.sin_port=htons(PortNum);
	}
	printf("socket created! to be setup with add:%s @%d\n",inet_ntoa(m_sLocalAddr.sin_addr),ntohs(m_sLocalAddr.sin_port));

	if(m_bIsServerMode) 
		iTryBind();
	else	
		iTryConnect();
}

//server mode to monitor socket ,server mode only
int CCommonSocket::iTryBind(){
	if(!m_bIsServerMode) return -1;
	//memset(m_sLocalAddr.sin_zero, 0x00, 8);
	if(bind(iLocalSocet,(struct sockaddr *)(&m_sLocalAddr), sizeof(m_sLocalAddr))<0)
	{
		printf("bind fail !\n");
	}
	printf("bind ok ! add:%s @%d\n",inet_ntoa(m_sLocalAddr.sin_addr),ntohs(m_sLocalAddr.sin_port));

	if(-1 == listen(iLocalSocet,100))
	{
		printf("listen fail !\n");
	}
	printf("[%s@%d] <-> wait for client...\n",inet_ntoa(m_sLocalAddr.sin_addr),ntohs(m_sLocalAddr.sin_port));
	return 0;
}


//client mode to connect the server,client mode only
int CCommonSocket::iTryConnect(){
	if(m_bIsServerMode) return -1;
	//memset(m_sRemoteAddr.sin_zero, 0x00, 8);
	printf("...try to connect <->[%s@%d]\n",inet_ntoa(m_sRemoteAddr.sin_addr),ntohs(m_sRemoteAddr.sin_port));
	//client use connect to "bind" scoket with remote(server) address 
	if (connect(iLocalSocet,(struct sockaddr *) &m_sRemoteAddr,sizeof(m_sRemoteAddr)) < 0) 
	{
	  printf("Failed to connect to case client deamon \n");
	  return -1;
	}
	m_SocketConnected= true;
	printf("success! client mode connect <->[%s@%d]\n",inet_ntoa(m_sRemoteAddr.sin_addr),ntohs(m_sRemoteAddr.sin_port));
	return 0;
}


int CCommonSocket::acceptConnect(){

	if(!m_bIsServerMode){
		printf("socket is not server mode, can not accepte connection\n");
		return -1;
	} 
	socklen_t sin_size = sizeof(m_sRemoteAddr);

	printf("[%s@%d] <-> wait for client...\n",inet_ntoa(m_sLocalAddr.sin_addr),ntohs(m_sLocalAddr.sin_port));
	iRemoteSocket = accept(iLocalSocet, (struct sockaddr *)(&m_sRemoteAddr), &sin_size);

	if(-1 == iRemoteSocket)
	{
	   printf("accept fail !\n");
	    return -1;
	}
	//printf("accept ok!\nServer start get connect from %s : %d\n",ntohl(m_sRemoteAddr.sin_addr.m_sLocalAddrr),ntohs(m_sRemoteAddr.sin_port));
	printf("found client!\nServer accpected connect from \n%s@%d <--> %s@%d\n",inet_ntoa(m_sLocalAddr.sin_addr),ntohs(m_sLocalAddr.sin_port),inet_ntoa(m_sRemoteAddr.sin_addr),ntohs(m_sRemoteAddr.sin_port));

	return 0;
}

int CCommonSocket::SocketSend(string text){
	//printf("trying to send %s\n",text.c_str());
	if(!m_bIsServerMode){
		if(!m_SocketConnected)
		{
			printf("not allow to send for local socket ipc client mode not connected\n");
			return -1;
		}
		if (send(iLocalSocet, text.c_str(), text.size(), 0) !=  text.size()) {
			printf("client:Mismatch in number of sent bytes[%d][%s]\n", text.size(),text.c_str() );
			return -1;
		}
	} 
	else
	{
	 	int inum=send(iRemoteSocket, text.c_str(), text.size(), 0);
		if(inum !=  text.size())
		printf("server:Mismatch in number of sent bytes![%d-%d][%s]\n",inum,  text.size(),text.c_str());
		return -1;
	}
	return 0;
}
static int ilastState = -1;
string CCommonSocket::SocketRecv()
{
	static bool bStateChanged = true;
	static int Nullcnt=0;
	int recbytes;
	memset(m_pbuffer,0,BUFSIZE);
	//if(-1 == (recbytes = read(iRemoteSocket,buffer,1024)))
	//use select to wait until msg received
	//select( int width£¬fd_set * readfds£¬fd_set * writefds£¬fd_set * exceptfds£¬         struct timeval * timeout );
	timeval tm;
	fd_set set;
	tm.tv_sec = 3;
	tm.tv_usec = 0;
	FD_ZERO(&set);
	FD_SET(iRemoteSocket, &set);
	if(!m_bIsServerMode)
	//if(1)
	{
	#if 0
		FD_ZERO(&set);
		FD_SET(iLocalSocet, &set);
		printf("Client socket blocked on  read data...\n");
		if (select(iLocalSocet + 1, NULL, &set, NULL, &tm) > 0)
		{
			printf("Client socket  read data success...\n");
		}
		else
		{
			printf("Client socke read data timer out !\n");
			return string("");
		}
	#endif
		if(-1 == (recbytes = recv(iLocalSocet,m_pbuffer,BUFSIZE,0)))
		{
			if(ilastState!=-1) printf("read data fail !\n");
			return string("");
		}
		ilastState = recbytes;

	}
	//if (select(iRemoteSocket + 1, NULL, &set, NULL, &tm) > 0)
	else
	{
		if(-1 == (recbytes = recv(iRemoteSocket,m_pbuffer,BUFSIZE,0)))
		{
			if(ilastState!=-1) printf("read data fail !\n");
			return string("");
		}
		ilastState = recbytes;
	}
	//else
	//{
	//	printf("read data timer out !\n");
	//	return string("");
	//}

	if(BUFSIZE<=recbytes)
	{
		printf("read buffer MAX\n");
		recbytes = BUFSIZE -1 ;
		bStateChanged = true;
	}
	else if(0==recbytes)
	{
		Nullcnt++;
		if(Nullcnt>=100)
		{
			Nullcnt=0;
			if(bStateChanged)
			{
				bStateChanged = false;
				printf("CCommonSocket::SocketRecv() --received zero length buffer \n");
			}
		}
		return string("");
	}
	printf("read %d words ok \nREC:\n",recbytes);
	//buffer[recbytes]='\0';
	//printf("%s\n",buffer);
	
	return(string(m_pbuffer));
}


void CCommonSocket::Disconnect(){
	close(iLocalSocet);
	
}

/*

void CCommonSocket::ReConnect(){
	acceptConnect();
}

void CCommonSocket::SetPortNum (unsigned short portnum){
	PortNum = portnum;
}*/

} // namespace CaseClient
} // namespace AFramework
} // namespace Adas
} // namespace Harman

