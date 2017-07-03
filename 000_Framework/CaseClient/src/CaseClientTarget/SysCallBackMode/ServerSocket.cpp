#include "ServerSocket.h" 
#include <sys/socket.h>
#include <sys/time.h>
#define BUFSIZE 40960
#define PORT 8888
#define TEST_IP_ADDRESS "127.0.0.1"
#define TAG_ENDOFCOMM "~"

#define XMLTAG_ROOT "CaseRoot"
#define XMLTAG_LIST "CaseList"
#define XMLTAG_CNAME "CaseName"
#define XMLTAG_OUTPUT "CaseOutput"
#define XMLTAG_INPUT "CaseInput"
#define XML_TITLE "<?xml version='1.0'?>"

#define XMLTAG_SINGLE_INPUT "SingleInput"
unsigned long getTickCount()
{
struct timespec ts;
clock_gettime(CLOCK_MONOTONIC, &ts);
return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}
//------------------------------CAdasServerSocket-------------------------------------
//------------------------------------------------------------------------------------

CAdasServerSocket::~CAdasServerSocket()
{
    close(sfp);
}


CAdasServerSocket::CAdasServerSocket()
{
	//set a tmp host name for case client auto connection
	int ierr=system("hostname CaseClientVersion001");
	if(ierr)
	{
		printf("set hostname as CaseClientVersion001 failed !\n");
	}
	else
	{
		printf("set hostname as CaseClientVersion001 successed !\n");
	}
	PortNum = PORT;

	sfp = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(-1 == sfp)
	{
	    printf("socket fail !\n");
	}
	printf("socket ok !\n");

	memset(&s_add,0,sizeof(s_add));
	s_add.sin_family=AF_INET;
	s_add.sin_addr.s_addr=htonl(INADDR_ANY);
	//s_add.sin_addr.s_addr=inet_addr(TEST_IP_ADDRESS);
	s_add.sin_port=htons(PortNum);
	memset(s_add.sin_zero, 0x00, 8);

	if(bind(sfp,(struct sockaddr *)(&s_add), sizeof(s_add))<0)
	{
	    printf("bind fail !\n");
	}
	printf("bind ok ! add:%s @%d\n",inet_ntoa(s_add.sin_addr),ntohs(s_add.sin_port));

	if(-1 == listen(sfp,100))
	{
	    printf("listen fail !\n");
	}
	printf("listen ok\n");
}


int CAdasServerSocket::acceptConnect(){

	socklen_t sin_size = sizeof(c_add);

	printf("wait client coming up ...\n");
	nfp = accept(sfp, (struct sockaddr *)(&c_add), &sin_size);

	if(-1 == nfp)
	{
	   printf("accept fail !\n");
	    return -1;
	}
	//printf("accept ok!\nServer start get connect from %s : %d\n",ntohl(c_add.sin_addr.s_addr),ntohs(c_add.sin_port));
	printf("accept ok!\nServer start get connect from %s : %d\n",inet_ntoa(c_add.sin_addr),ntohs(c_add.sin_port));

	return 0;
}

int CAdasServerSocket::SocketSend(string text){

	if(-1 ==send(nfp,text.c_str(),text.size(),0))
	{
		printf("CAdasServerSocket send msg fail!\n");
		return -1;
	}
	return 0;
}

static char buffer[BUFSIZE]={0};
string CAdasServerSocket::SocketRecv()
{
	static bool bStateChanged = true;
	static int Nullcnt=0;
	int recbytes;
	memset(&buffer,0,sizeof(buffer));
	//if(-1 == (recbytes = read(nfp,buffer,1024)))
	//use select to wait until msg received
	//select( int width£¬fd_set * readfds£¬fd_set * writefds£¬fd_set * exceptfds£¬         struct timeval * timeout );
	timeval tm;
	fd_set set;
	tm.tv_sec = 3;
	tm.tv_usec = 0;
	FD_ZERO(&set);
	FD_SET(nfp, &set);
	if (select(nfp + 1, NULL, &set, NULL, &tm) > 0)
	{
		if(-1 == (recbytes = recv(nfp,buffer,BUFSIZE,0)))
		{
			printf("read data fail !\n");
			return string("");
		}
	}
	else
	{
		printf("read data timer out !\n");
		return string("");
	}

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
				printf("CAdasServerSocket::SocketRecv() --received zero length buffer \n");
			}
		}
		return string("");
	}
	printf("read %d words ok \nREC:\n",recbytes);
	//buffer[recbytes]='\0';
	//printf("%s\n",buffer);
	
	return(string(buffer));
}


void CAdasServerSocket::Disconnect(){
	close(sfp);
	
}

void CAdasServerSocket::ReConnect(){
	acceptConnect();
}

void CAdasServerSocket::SetPortNum (unsigned short portnum){
	PortNum = portnum;
}


//----------------------------CAdasSocketManager---------------------------------
//---------------------------------------------------------------------------------

CAdasSocketManager*  CAdasSocketManager::s_pInstance=NULL;

CAdasSocketManager* CAdasSocketManager::getInstance()
{
   if(s_pInstance == NULL)
   {
	   s_pInstance = new CAdasSocketManager();
   }
   return s_pInstance;
}


void CAdasSocketManager::delInstance()
{
	delete s_pInstance;
	s_pInstance = NULL;
}

CAdasSocketManager::~CAdasSocketManager()
{
	CommandSet.clear();
	s_pInstance = NULL;
	delete m_ServerSocket;
	m_ServerSocket = NULL;
	delete m_caseXmlDoc;
	m_caseXmlDoc = NULL;
}


CAdasSocketManager::CAdasSocketManager(){

	m_ServerSocket = new CAdasServerSocket();
	m_caseXmlDoc = new tinyxml2::XMLDocument();
}


int CAdasSocketManager::CAdasAcceptConnect(){

	int err = m_ServerSocket->acceptConnect();
	return err;
}


void CAdasSocketManager::CAdasSendResult(string text){

	m_ServerSocket->SocketSend(text);
}


string CAdasSocketManager::CAdasRecvCommand(){
	string CaseCommand = m_ServerSocket->SocketRecv();
	return CaseCommand;
}

//pick input to command bufffer 
void CAdasSocketManager::CAdasParseXML(string text){

	//bool bOnePackageReady = false;
	static string sOneCasePackage(" ");

	CommandSet.clear();
	m_caseXmlDoc->Clear();
	//to adport case assitant side add caseroot and and caselist
	//for case client mode we add case root to let windows side parse.....,
	//found a bug to parsse it on long text...  now we remove it for syscall mode

	sOneCasePackage+=text;
	//string tmpText = string("<?xml version=\"1.0\"?>")+string("<CaseRoot>") +string("<CaseList attrib=\"CaseClint Online Case\">") + sOneCasePackage + string( "</CaseList>") +string("</CaseRoot>");

	m_caseXmlDoc->Parse(sOneCasePackage.data());

	tinyxml2::XMLElement* xElement = m_caseXmlDoc->FirstChildElement(XMLTAG_SINGLE_INPUT);
	//try run single input item mode first
	if(xElement)
	{
		tinyxml2::XMLPrinter printer;
		m_caseXmlDoc->Print(&printer);

		printf("run single input item:\n %s\n",printer.CStr());
		sOneCasePackage =" ";
	}
	else
	{
		xElement = m_caseXmlDoc->FirstChildElement(XMLTAG_CNAME);
		//titleElement->FirstChildElement(XMLTAG_LIST);
		if (xElement == NULL)
		{
			//bOnePackageReady =false;
			printf("CAdasSocketManager : package of case info is not ready\n");
			return;
		}
		else
		{
			//bOnePackageReady = true;
			sOneCasePackage =" ";
		}
		//titleElement =  titleElement->FirstChildElement(XMLTAG_CNAME);
		//system call mode - need to echo all the case item into test interface on adas serivce "echo "
		//cause need adas serivce itself to sync this event  -- if adas integrated with case client , then no need to echo other infos
		xElement = xElement->FirstChildElement(XMLTAG_INPUT);
		if (xElement == NULL)
		{
			printf("CAdasSocketManager:inputElement not found \n");
			return;
		}
		printf("successfully parsed one case xml!\n");
	}
	CommandSet.push_back(xElement->GetText());

	while(xElement->NextSiblingElement(XMLTAG_INPUT)!=NULL){
		xElement = xElement->NextSiblingElement(XMLTAG_INPUT);
		CommandSet.push_back(xElement->GetText());
	}
	//to make queue and run case input
	while(xElement->NextSiblingElement(XMLTAG_SINGLE_INPUT)!=NULL){
		xElement = xElement->NextSiblingElement(XMLTAG_SINGLE_INPUT);
		CommandSet.push_back(xElement->GetText());
	}
}

//insert output after case is done - based on sync control
string CAdasSocketManager::CAdasConstructXML(){

	tinyxml2::XMLElement* titleElement = m_caseXmlDoc->FirstChildElement(XMLTAG_CNAME);
	vector<string>::iterator it = LogSet.begin();
	for(unsigned int i = 0; i< LogSet.size() ; i++){
		tinyxml2::XMLElement* outputElement = m_caseXmlDoc->NewElement(XMLTAG_OUTPUT);
		outputElement->SetText(it[i].data());
		titleElement->InsertEndChild(outputElement);
	}

	tinyxml2::XMLPrinter printer;
	m_caseXmlDoc->Print(&printer);
	string tmpt = printer.CStr();
	return tmpt;
}


//TODO : command mode
//command mode 1: system call - dependency on services
//command mode 2: call back call

//TODO global delay on run cases
void CAdasSocketManager::CAdasExcuteCommand(){
	LogSet.clear();
	vector<string>::iterator it = CommandSet.begin();
	//--TODO: Callback function ---
	printf("******************enter time: %u********************\n", getTickCount());
	for(unsigned int i = 0; i< CommandSet.size(); i++){
		//printf(" system try call :%s\n ",CommandSet[i].c_str());
		int retval = system(CommandSet[i].c_str());
		if(retval){printf("CaseClient system call failed on [%s]\n ",CommandSet[i].c_str());}
	}
	printf("******************exit time: %u********************\n",getTickCount());
}

string CAdasSocketManager::dumpstr(){
	tinyxml2::XMLPrinter printer;
	m_caseXmlDoc->Print(&printer);
	return printer.CStr();
}


/*
//----------------------------CCommandLineParser---------------------------------
//---------------------------------------------------------------------------------
CCommandLineParser::CCommandLineParser()
{
}

CCommandLineParser::~CCommandLineParser()
{
}


void CCommandLineParser::process(const string& strName, char* buf)
{
	HashMap<string, CFunctor*>::Iterator it= m_hashMapFunctor.find(strName);
	if( it!= m_hashMapFunctor.end() )
	{
		CFunctor* pfunctor = (*it).second;
		string strData(buf);
		(*pfunctor)(strData);
	}
	return;
}

void CCommandLineParser::registerFunctor(const string& strName, CFunctor* pFunctor)
{
	if( pFunctor )
		m_hashMapFunctor.insert( makePair(strName,pFunctor) );
}
*/
