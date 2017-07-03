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

using namespace std;

#define COMMAND1 "COMMAND1"



class CAdasServerSocket{

public:
	CAdasServerSocket();
	~CAdasServerSocket();
	int setupEnv();
	int acceptConnect();
	void ReConnect();
	void Disconnect();
	int SocketSend(string text);
	string SocketRecv();
	void SetPortNum (unsigned short portnum);

private:
	int sfp;
	int nfp;
	struct sockaddr_in s_add;
	struct sockaddr_in c_add;
	unsigned short PortNum;
	bool m_ServerConnected;	
};


class CAdasSocketManager{
public:
	static CAdasSocketManager* 	getInstance();
    static void 			delInstance();
    virtual ~CAdasSocketManager();
	int  CAdasAcceptConnect();
	void CAdasSendResult(string text);
	string CAdasRecvCommand();
	string CAdasConstructXML();
	void CAdasParseXML(string text);
	void CAdasExcuteCommand();
    //debug
    string dumpstr();

private:
	CAdasSocketManager();
	static CAdasSocketManager*  s_pInstance;
	vector<string> CommandSet;
	vector<string> LogSet;
	CAdasServerSocket * m_ServerSocket;
	tinyxml2::XMLDocument* m_caseXmlDoc;
};

/*
class CCommandLineParser
{

public:
	 CCommandLineParser();
	virtual ~ CCommandLineParser();
	void	process(const string& strName, char* buf);

protected:
	void	registerFunctor(const string& strName, CFunctor* pFunctor);
private:// data
	HashMap<string, CFunctor*>	m_hashMapFunctor;
};
*/
