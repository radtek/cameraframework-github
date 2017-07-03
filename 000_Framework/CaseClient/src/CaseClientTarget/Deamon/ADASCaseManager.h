#ifndef _ADASCASEMANAGER_H_
#define _ADASCASEMANAGER_H_
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>

#include <vector>
#include <queue>
#include <string>
#include "../../../include/ServerSocket.h"
#include "tinyxml2.h"
using namespace std;
using namespace Harman::Adas::AFramework::CaseClient;

#define COMMAND1 "COMMAND1"

//todo : separate command as command object
class CAdasCaseManager{
public:
	//static CAdasCaseManager* 	getInstance();
    //static void 			delInstance();
    CAdasCaseManager(string sIP, int iPort);
    virtual ~CAdasCaseManager();
	int  CAdasAcceptConnect();
	void CAdasSendResult(string text);
	string CAdasRecvCommand();
	string CAdasConstructXML();
	void CAdasParseXML(string text);
	void CAdasExcuteCommand();
	bool bIsSingleCommandMode() {return m_bSingleCommandMode;};
    //debug
    string dumpstr();

private:
	
	//static CAdasCaseManager*  s_pInstance;
	queue<string> CommandSet;
	queue<string> LogSet;
	CCommonSocket * m_ServerSocket;
	tinyxml2::XMLDocument* m_caseXmlDoc;
	bool m_bSingleCommandMode;
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
#endif
