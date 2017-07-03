
#include <sys/time.h>
#include "ADASCaseManager.h"
//to support api mode , need socket instance
#include "CaseLogCollector.h"

#define BUFSIZE 40960*10

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
//----------------------------CAdasCaseManager---------------------------------
//---------------------------------------------------------------------------------
/*
CAdasCaseManager*  CAdasCaseManager::s_pInstance=NULL;

CAdasCaseManager* CAdasCaseManager::getInstance()
{
   if(s_pInstance == NULL)
   {
	   s_pInstance = new CAdasCaseManager();
   }
   return s_pInstance;
}


void CAdasCaseManager::delInstance()
{
	delete s_pInstance;
	s_pInstance = NULL;
}
*/
CAdasCaseManager::~CAdasCaseManager()
{
	while(!CommandSet.empty()){CommandSet.pop();};
	while(!LogSet.empty()){LogSet.pop();};
	delete m_ServerSocket;
	m_ServerSocket = NULL;
	delete m_caseXmlDoc;
	m_caseXmlDoc = NULL;
}


CAdasCaseManager::CAdasCaseManager(string sIP, int iPort){

	m_ServerSocket = new CCommonSocket(sIP.c_str(),iPort,true);
	m_caseXmlDoc = new tinyxml2::XMLDocument();
	m_bSingleCommandMode =true;
}


int CAdasCaseManager::CAdasAcceptConnect(){

	int err = m_ServerSocket->acceptConnect();
	return err;
}


void CAdasCaseManager::CAdasSendResult(string text){

	m_ServerSocket->SocketSend(text);
}


string CAdasCaseManager::CAdasRecvCommand(){
	string CaseCommand = m_ServerSocket->SocketRecv();
	return CaseCommand;
}
//从字符串开始处依次替换子字符串
string&   replace_all_distinct(string&   str,const   string&   old_value,const   string&   new_value)
{
    for(string::size_type   pos(0);   pos!=string::npos;   pos+=new_value.length())   {
        if(   (pos=str.find(old_value,pos))!=string::npos   )
            str.replace(pos,old_value.length(),new_value);
        else   break;
    }
    return   str;
}

void  replace_all_quote(string&  aa)
{
	if(string::npos==aa.find("echo")) return;
	if(string::npos==aa.find('\"')) return;
    size_t headindex=aa.find_first_of('\"');
	string subHead=aa.substr(0,headindex+1);
    size_t tailindex=aa.find_last_of('\"');
	string subTail=aa.substr(tailindex,aa.size());
	string tmp=aa.substr(headindex+1,tailindex -headindex-1);
	if(string::npos!=tmp.find('\"')) replace_all_distinct(tmp,"\"","\\\"");
	string bb=subHead + tmp + subTail;
	aa = bb;
}

//pick input to command bufffer 
void CAdasCaseManager::CAdasParseXML(string text){

	//bool bOnePackageReady = false;
	static string sOneCasePackage("");

	if(!CommandSet.empty()) printf("error: CAdasCaseManager::CAdasParseXML runs but cmd buffer not empty ,remains:%d\n",CommandSet.size());
	while(!CommandSet.empty()){CommandSet.pop();};
	m_caseXmlDoc->Clear();
	//to adport case assitant side add caseroot and and caselist
	//for case client mode we add case root to let windows side parse.....,
	//found a bug to parsse it on long text...  now we remove it for syscall mode

	sOneCasePackage+=text;
	//string tmpText = string("<?xml version=\"1.0\"?>")+string("<CaseRoot>") +string("<CaseList attrib=\"CaseClint Online Case\">") + sOneCasePackage + string( "</CaseList>") +string("</CaseRoot>");

	m_caseXmlDoc->Parse(sOneCasePackage.data());

	tinyxml2::XMLElement* xElement = m_caseXmlDoc->FirstChildElement(XMLTAG_SINGLE_INPUT);
	//try run single input item mode first
	tinyxml2::XMLPrinter printer;
	m_caseXmlDoc->Print(&printer);
	if(xElement)
	{
		printf("CaseClient run single input mode:\n==================\n%s\n==================\n",printer.CStr());
		sOneCasePackage ="";
	}
	else
	{
		//debug
		printf("CaseClient run use case mode:\n==================\n%s\n==================\n",printer.CStr());
	
		xElement = m_caseXmlDoc->FirstChildElement(XMLTAG_CNAME);
		//titleElement->FirstChildElement(XMLTAG_LIST);
		if (xElement == NULL)
		{
			//bOnePackageReady =false;
			printf("CAdasCaseManager : package of case info is not ready\n");
			return;
		}
		else
		{
			//bOnePackageReady = true;
			sOneCasePackage ="";
		}
		//titleElement =  titleElement->FirstChildElement(XMLTAG_CNAME);
		//system call mode - need to echo all the case item into test interface on adas serivce "echo "
		//cause need adas serivce itself to sync this event  -- if adas integrated with case client , then no need to echo other infos
		xElement = xElement->FirstChildElement(XMLTAG_INPUT);
		if (xElement == NULL)
		{
			printf("CAdasCaseManager:inputElement not found \n");
			return;
		}
		printf("successfully parsed one case xml!\n");
	}
	string sTmp;
	sTmp=xElement->GetText();
	replace_all_quote(sTmp);
	CommandSet.push(sTmp);
	m_bSingleCommandMode = true;//reset command mode
	while(xElement->NextSiblingElement(XMLTAG_INPUT)!=NULL){
		xElement = xElement->NextSiblingElement(XMLTAG_INPUT);
		sTmp=xElement->GetText();
		replace_all_quote(sTmp);
		CommandSet.push(sTmp);
		m_bSingleCommandMode = false;
	}
	if(!m_bSingleCommandMode) return;//not run single command if case command is received

	//to make queue and run case input
	while(xElement->NextSiblingElement(XMLTAG_SINGLE_INPUT)!=NULL){
		xElement = xElement->NextSiblingElement(XMLTAG_SINGLE_INPUT);
		sTmp=xElement->GetText();
		replace_all_quote(sTmp);
		CommandSet.push(sTmp);
		m_bSingleCommandMode = true;
	}
}

//insert output after case is done - based on sync control
string CAdasCaseManager::CAdasConstructXML(){

	tinyxml2::XMLElement* titleElement = m_caseXmlDoc->FirstChildElement(XMLTAG_CNAME);
	while(!LogSet.empty())
	{
		tinyxml2::XMLElement* outputElement = m_caseXmlDoc->NewElement(XMLTAG_OUTPUT);
		outputElement->SetText(LogSet.front().data());
		titleElement->InsertEndChild(outputElement);
		LogSet.pop();
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
static string sWorkMode = "ModeSysCall";
static unsigned int g_iCntRun=0;
void CAdasCaseManager::CAdasExcuteCommand(){
	g_iCntRun++;
	//--TODO: Callback function ---
	string sTmp;
	printf("CaseCMD [%d] ==>enter time: %u********************\n", g_iCntRun,getTickCount());
	while(!CommandSet.empty()){
		//printf(" system try call :%s\n ",CommandSet[i].c_str());
//if command is SetModeSysCall, then set mode and wait for next command 
		sTmp = CommandSet.front();

		if(("[Str]"==sTmp.substr(0,5)))
		{
			//common string mode[ms2016 vs GWMv2]
			//test target side to directly loop back to side
			//printf(" case client side should loop back string [%s]\n ",sTmp.substr(5,sTmp.size()).c_str());
			CCaseLogCollector::getInstance()->vSetAck();	
			CCaseLogCollector::getInstance()->vSendStr(sTmp.c_str());
			//todo !! start a timer to protect no ack from test target
			CCaseLogCollector::getInstance()->vWaitAck();	
			printf(" case client side received ack for  loop back string [%s]\n ",sTmp.substr(5,sTmp.size()).c_str());
			//block until test target replys receved one command str
		}
		else if(("ModeSysCall"==sTmp)||("ModeApiCall"==sTmp))

		{
			sWorkMode = sTmp;
			printf(" case deamon work mode updated to [%s]\n ",sWorkMode.c_str());
		}
		else
		{
			if("ModeSysCall"==sWorkMode)
			{
				int retval = system(sTmp.c_str());
				printf("-->excuted command\n%s\n",sTmp.c_str());
				if(retval){printf("CaseClient system call failed on [%s]\n ",sTmp.c_str());};
			}
			else if("ModeApiCall"==sWorkMode)
			{
				CCaseLogCollector::getInstance()->vSetAck();
				CCaseLogCollector::getInstance()->vSendStr(sTmp.c_str());
				CCaseLogCollector::getInstance()->vWaitAck();
				//block until test target replys receved one command str
				
			}
		}
		CommandSet.pop();
	}
	printf("CaseCMD [%d] <==exit time: %u********************\n",g_iCntRun,getTickCount());
}

string CAdasCaseManager::dumpstr(){
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
